#! /usr/bin/env python3

# -*- coding: utf-8 -*-
"""
@author: sawhite
@date:   2018-06-19
@brief:  Archives scenario runs to create new rebases
"""
import sys, shutil
import os
import re
import zipfile
import zlib
import argparse
import subprocess
"""
Arguments:
  --root    -- <Path to the root of a biogears run>
  --outdir  -- <Intended destination of the rebase results>
Possible Commands
    [-r] archive PATH  -- <Path to a single Results file or a Directory of Results relative to --input-dir if provided>
    [-r] rebase FILEPATH | -all  Runs scenario driver for every *.xml 
"""
_log_verbose = 0
LOG_LEVEL_0 = 0
LOG_LEVEL_1 = 1
LOG_LEVEL_2 = 2
LOG_LEVEL_3 = 3
LOG_LEVEL_4 = 4

_output_directory  = None
_root_directory    = None
_runtime_directory = None
_scenario_driver    = None
_clean_directory  = False
archive_extension    = ".zip"
_baseline_dir     = "baselines"
_compression_format = 'zlib'

def main( args):
    global _log_verbose
    global _root_directory
    global _output_directory
    global _clean_directory

    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--verbose', help="Adjust the log verbosity.", dest='verbosity', default=0, action='count' )
    parser.add_argument('--version', action='version', version='%(prog)s 1.0')
    parser.add_argument('--root',
        dest='root', action="store", 
        help="Appended to all input PATHS when provided", default="")
    parser.add_argument('--outdir',
        dest='outdir', action="store", 
        help="Optional Output directory instead of inlinline layout")
    
    subparsers = parser.add_subparsers(help='sub-command help', dest='sub_cmd')

    common_flags = argparse.ArgumentParser(add_help=False)
    common_flags.add_argument('-r', '--recursive', dest='recurse', action='store_true' ,help='Activates recursive mode')
    common_flags.add_argument('-c', '--cleanup', dest='clean',  action='store_true' ,help='Activates recursive mode')
    common_flags.add_argument('-z', '--compression', type=str, choices=['zlib','bzip','lzma'], default='zlib' )
    
    archive = subparsers.add_parser('archive',  parents=[common_flags], help='Archives existing runs to a base_line directory.')
    archive.add_argument('path', type=str, help='Source to be archived')    
    archive.set_defaults(func=archive_command)
    
    rebase = subparsers.add_parser('rebase', parents=[common_flags], help='runs scenarios and archives the results')
    rebase.add_argument('--workdir', type=str, help="directory which the given driver will be run. Assumed to be Root unless given")
    rebase.add_argument('driver', type=str, help="Path to an executable biogears scenario driver")
    rebase.add_argument('path', type=str, help='Scenario file to run')
    rebase.set_defaults(func=rebase_command)
    args = parser.parse_args()

    _log_verbose = args.verbosity
    _root_directory = args.root if args.root else "./"
    _output_directory = args.outdir if args.outdir else _root_directory

    log( "log_levle: {0}\nroot: {1}\noutput: {2}".format(_log_verbose,_root_directory,_output_directory), LOG_LEVEL_2 )
    if args.sub_cmd is None:
        parser.print_usage()
    else:
        args.func(args)

def archive_command(args):
    global _compression_format
    _compression_format = args.compression
    if(args.clean):
        cleanup(_output_directory)
    archive(args.root, args.path, args.recurse, False)

def archive (root, path, recurse, clean):
    log( "archive(root:{0}, path:{1}, recurse:{2}, clean:{3})".format(root,path,recurse,clean), LOG_LEVEL_2 )
    valid_regex = '[.](txt|csv)'
    absolute_path = os.path.join(root ,path)
    basename,extension     = os.path.splitext(absolute_path)
    output_path = os.path.join(_output_directory,os.path.relpath(basename,_root_directory))
    if( os.path.isfile(absolute_path) ):
        if ( re.match( valid_regex, extension) ):
            destination  = os.path.join( os.path.dirname(output_path) , _baseline_dir )
            compress_and_store(absolute_path, destination)
            
    elif(os.path.isdir(absolute_path)):
        if(recurse):
            for file in os.listdir(absolute_path):
                archive(absolute_path,file,recurse,clean)
            pass
        else:
            err("{0} is a directory.".format(absolute_path),LOG_LEVEL_0)
    else:
        err("{0} is not a valid results file".format(absolute_path),LOG_LEVEL_0)

def rebase_command(args):
    global _runtime_directory
    global _scenario_driver
    global _compression_format
    _runtime_directory = args.workdir if args.workdir else _root_directory
    _scenario_driver = args.driver if args.driver else scenario-driver
    _compression_format = args.compression
    if(args.clean):
        cleanup(_output_directory)
    rebase(args.root, args.path, args.recurse, False)

def rebase (root, path, recurse, clean):
    log( "rebase(root:{0}, path:{1}, recurse:{2}, clean:{3})".format(root,path,recurse,clean), LOG_LEVEL_2 )
    valid_regex = '[.](xml)'
    absolute_path = os.path.join(root ,path)
    basename,extension     = os.path.splitext(absolute_path)
    output_path = os.path.join(_output_directory,os.path.relpath(basename,_root_directory))
    if( os.path.isfile(absolute_path) ):
        if ( re.match( valid_regex, extension) ):
            #Execute Rebase Utility
            p = subprocess.Popen([_scenario_driver,absolute_path], stderr=subprocess.STDOUT, cwd=_runtime_directory)
            p.wait()
            destination  = os.path.join( os.path.dirname(output_path) , _baseline_dir )
            results = basename+"Results.csv";
            if( os.path.exists(results)):
                compress_and_store(results, destination)
            else:
                err("Unable to locate {0}".format(results), LOG_LEVEL_0)
    elif(os.path.isdir(absolute_path)):
        if(recurse):
            for file in os.listdir(absolute_path):
                rebase(absolute_path,file,recurse,clean)
            pass
        else:
            err("{0} is a directory.".format(absolute_path),LOG_LEVEL_0)
    else:
        err("{0} is not a valid results file".format(absolute_path),LOG_LEVEL_0)

def compress_and_store(source,destination):
    source_dir  =  os.path.dirname(source)
    source_name =  os.path.basename(source)
    name, ext   =  os.path.splitext(source_name)
    archive_name = name + archive_extension

    rcode = True
    if ( not os.path.exists( destination )):
        os.makedirs( destination )

    archive = os.path.join(destination, archive_name)
    
    if ( os.path.exists( archive) ):
        try:
            log("removing {0}".format(archive),LOG_LEVEL_2)
            os.remove(archive)
        except OSError:
            err("Unable to remove {0}".format(archive), LOG_LEVEL_0A)
    if os.path.exists(source):
        log("{0} -> {1}".format(source,archive),LOG_LEVEL_1)

        format = zipfile.ZIP_DEFLATED
        if _compression_format == 'lzma':
            format = zipfile.ZIP_LZMA
        elif _compression_format == 'bzip':
            format = zipfile.ZIP_BZIP2
        
        zip = zipfile.ZipFile( archive , mode='w', compression=format )
        try:
            log( "Archiving {0} in {1}".format(source,archive), LOG_LEVEL_2)
            zip.write( source, source_name )

            result_log_name = source_name.replace('Results.csv','.csv').replace('.csv','.log')
            result_log_path = os.path.join(source_dir,result_log_name)
            if( os.path.exists( result_log_path) ):
              zip.write( result_log_path, result_log_name )
            else:
              log("No file {} found".format(result_log_path),LOG_LEVEL_2)
            
              test_log_name = source_name.replace('.csv','Test.log')
              test_log_path = os.path.join(source_dir,test_log_name)
              if( os.path.exists(test_log_path) ): 
                zip.write( test_log_path, test_log_name )
              else:
                log("No file {} found".format(test_log_path),LOG_LEVEL_2)

        except ValueError:
            err("Unable to write to {0}".format(archive), LOG_LEVEL_0)
            rcode = False
        zip.close()
    else:
        err("{} does not exists".format(source),LOG_LEVEL_0)
        rcode = False
    return rcode

"""
This function is very dangerous.
INPUT dir -- directory or file to be deleted

@description
IF dir == _input_directory bail else delete the path
"""
def cleanup( dir ):
    if ( dir != _root_directory ):
        if (os.path.isfile(dir)):
            print(os.remove(dir))
        elif (os.path.isdir(dir)):
            print(shutil.rmtree(dir))
        else :
            err ("outdir does not exist.", LOG_LEVEL_2)
    else:
        err("Cannot cleanup outdir which is set to indir", LOG_LEVEL_0)

def err(message, level):
    print( "{}\n".format(message) if _log_verbose >= level else "" , end="", file=sys.stderr)
def log(message, level):
    print( "{}\n".format(message) if _log_verbose >= level else "" , end="")
    
if __name__ == "__main__":
    # execute only if run as a script
    main( sys.argv )
