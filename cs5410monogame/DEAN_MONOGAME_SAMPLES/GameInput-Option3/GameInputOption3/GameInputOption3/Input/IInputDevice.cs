using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework;

namespace InputLab.Input
{
	/// <summary>
	/// Abstract base class that defines how input is presented to game code.  All input
	/// is performed through derived classes, but accessed through this class's interface
	/// </summary>
	public interface IInputDevice
	{
		void registerCommand(Keys key, bool keyPressOnly, InputDeviceHelper.CommandDelegate callback);
		void registerCommand(Buttons button, bool buttonPressOnly, InputDeviceHelper.CommandDelegate callback);

		void Update(GameTime gameTime);
	}

	public class InputDeviceHelper
	{
		public delegate void CommandDelegate(GameTime gameTime, float value);
	}
}
