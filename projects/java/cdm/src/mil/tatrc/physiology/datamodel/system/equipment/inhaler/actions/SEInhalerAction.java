/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

package mil.tatrc.physiology.datamodel.system.equipment.inhaler.actions;

import mil.tatrc.physiology.datamodel.bind.AnesthesiaMachineActionData;
import mil.tatrc.physiology.datamodel.bind.InhalerActionData;
import mil.tatrc.physiology.datamodel.scenario.actions.SEAction;

public abstract class SEInhalerAction extends SEAction
{
	public SEInhalerAction()
	{
		
	}
	
	public void copy(SEInhalerAction other)
	{
		if (this == other)
			return;
		super.copy(other);
	}
	
	public void reset()
	{
		super.reset();
	}
	
	public boolean load(InhalerActionData in)
	{
		super.load(in);
		return true;
	}
	
	protected void unload(InhalerActionData data)
	{
		super.unload(data);
	}
	
	public abstract String toString();
}
