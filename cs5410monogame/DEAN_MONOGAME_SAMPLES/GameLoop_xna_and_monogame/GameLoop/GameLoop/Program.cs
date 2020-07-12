using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameLoop
{
	class Program
	{
		static void Main(string[] args)
		{
			MyGame Game = new MyGame();
			Game.Initialize();
			Game.Run();
		}
	}
}
