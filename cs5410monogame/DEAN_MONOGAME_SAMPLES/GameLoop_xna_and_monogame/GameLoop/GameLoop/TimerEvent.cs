using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameLoop
{
	/// <summary>
	/// This is a timer event that goes off every so many milliseconds,
	/// for some number of times.
	/// </summary>
	public class TimerEvent
	{
		public TimerEvent(double When, int HowMany, string Message)
		{
			this.When = When;
			this.HowMany = HowMany;
			this.Message = Message;
			this.Elapsed = 0;
		}

		public double When;
		public double Elapsed;
		public int HowMany;
		public string Message;
	}
}
