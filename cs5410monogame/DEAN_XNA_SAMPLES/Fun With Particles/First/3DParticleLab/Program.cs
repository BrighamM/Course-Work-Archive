using System;

namespace ParticleLab
{
	static class Program
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		static void Main(string[] args)
		{
			using (MagicNumbersAbound game = new MagicNumbersAbound())
			{
				game.Run();
			}
		}
	}
}

