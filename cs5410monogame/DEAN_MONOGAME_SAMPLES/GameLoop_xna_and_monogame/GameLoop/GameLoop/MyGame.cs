/*
 * 
 * 
 * I AM TRYING TO MAKE THIS REALLY OBVIOUS!!!!!
 * IF YOU ARE USING 
 * 
 * MONODEVELOP (LINUX) 
 * OR
 * VISUAL STUDIO 2019 (MAC)
 * 
 * THEN YOU 
 * NEED TO GO TO:
 * Run -> Run With -> Custom Configuration -> 
 * [Check the box that says run on external console]
 * 
 * 
 * 
 */



using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameLoop
{
	public class MyGame
	{
		/// <summary>
		/// Do any game initialization right here
		/// </summary>
		public void Initialize()
		{
			Console.WriteLine("GameLoop Demo Initializing...");

			Console.Write(CommandPrompt);
			this.TimeBefore = DateTime.Now;
			this.Done = false;

			this.InputBuffer = null;
			this.Events = new List<TimerEvent>();

            this.RenderQueue = new Queue<string>();
		}

		/// <summary>
		/// The is the main "Game Loop".  This method does not return until the game is done
		/// </summary>
		public void Run()
		{
			while (!this.Done)
			{
				//
				// Compute the difference in time
				DateTime timeAfter = DateTime.Now;
				TimeSpan timeElapsed = timeAfter - this.TimeBefore;
				//
				// Replace the before time with the current time
				this.TimeBefore = timeAfter;

				//
				// Accept user input, update the simulation
				Update(timeElapsed);

				//
				// "Render" States
				Render();
			}

			Console.WriteLine();
			Console.WriteLine("GameLoop Demo Complete");
		}

		/// <summary>
		/// Accept user input and update the simulation
		/// </summary>
		protected void Update(TimeSpan elapsedTime)
		{
			//
			// Only accept input if something is available
			if (Console.KeyAvailable)
			{
				//
				// Get user input
				ConsoleKeyInfo key = Console.ReadKey(true);

				if (key.Key == ConsoleKey.Enter)
				{
					//
					// Execute the command
					this.Done = executeCommand(this.InputBuffer);
                    this.RenderQueue.Enqueue("\n" + CommandPrompt);
                    this.InputBuffer = null;
				}
				else if (key.Key == ConsoleKey.Backspace)
				{
					//
					// remove the last item
					if (this.InputBuffer.Length > 0)
					{
						InputBuffer = this.InputBuffer.Substring(0, this.InputBuffer.Length - 1);
                        this.RenderQueue.Enqueue(string.Format("\n{0} {1}", CommandPrompt, this.InputBuffer));
					}
				}
				else
				{
					this.InputBuffer += key.KeyChar;
                    this.RenderQueue.Enqueue(key.KeyChar.ToString());
				}
			}

			//
			// Update States
			List<TimerEvent> Expired = new List<TimerEvent>();
			foreach (TimerEvent e in this.Events)
			{
				e.Elapsed += elapsedTime.TotalMilliseconds;
				if (e.HowMany == 0)
				{
					Expired.Add(e);
				}
			}

			//
			// Remove any events that have expired
			foreach (TimerEvent e in Expired)
			{
				this.Events.Remove(e);
			}
		}

		/// <summary>
		/// "Render" the state of the simulation
		/// </summary>
		protected void Render()
		{
			bool eventFired = false;
			foreach (TimerEvent e in this.Events)
			{
				if (e.Elapsed >= e.When)
				{
                    this.RenderQueue.Enqueue(string.Format("\n\tEvent Fired : {0}", e.Message, e.Elapsed));
					e.Elapsed = 0;
					e.HowMany--;
					eventFired = true;
				}
			}

			if (eventFired)
			{
				this.RenderQueue.Enqueue(string.Format("\n{0} {1}", CommandPrompt, this.InputBuffer));
			}

            //
            // This is where we will display everything that has been queued for display
            foreach (string item in this.RenderQueue)
            {
                Console.Write(item);
            }
            this.RenderQueue.Clear();
		}

		/// <summary>
		/// Examine the input buffer and see if there are any commands to execute
		/// </summary>
		private bool executeCommand(string commandString)
		{
			if (commandString == null) return false;

			if (commandString.ToUpper() == "QUIT")
			{
				return true;
			}

			if (commandString.ToUpper().Contains("CREATE EVENT"))
			{
				//
				// Make sure there are the correct number of parts to the string
				string[] Parts = commandString.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

                this.RenderQueue.Enqueue("\n UH OH " + MyGame.CreateEventParts.ToString() + " " + Parts.Length.ToString());

                if (Parts.Length == MyGame.CreateEventParts)
				{
					try
					{
						double When = double.Parse(Parts[MyGame.PositionEventTime]);
						int HowMany = int.Parse(Parts[MyGame.PositionEventCount]);
						TimerEvent MyEvent = new TimerEvent(When, HowMany, Parts[MyGame.PositionEventName]);
						this.Events.Add(MyEvent);
					}
					catch
					{
                        this.RenderQueue.Enqueue("\nInvalid parameters");
					}
				}
			}
            else
            {
                this.RenderQueue.Enqueue("\nInvalid command");
            }



			return false;
		}

		#region Properties

		protected bool Done { get; set; }
		protected DateTime TimeBefore { get; set; }

		private string InputBuffer { get; set; }
		private List<TimerEvent> Events { get; set; }

        private Queue<string> RenderQueue { get; set; }

		#endregion

		private const string CommandPrompt = "[cmd:] ";
		private const int CreateEventParts = 5;
		private const int PositionEventName = 2;
		private const int PositionEventTime = 3;
		private const int PositionEventCount = 4;
	}
}
