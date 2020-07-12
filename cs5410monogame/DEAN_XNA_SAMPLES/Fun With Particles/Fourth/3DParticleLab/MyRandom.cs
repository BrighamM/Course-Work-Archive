using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace ParticleLab
{
	/// <summary>
	/// Expands upon some of the features the .NET Random class does:
	/// 
	/// *NextRange : Generate a random number within some range
	/// *NextGaussian : Generate a normally distributed random number
	/// 
	/// </summary>
	class MyRandom : Random
	{

		/// <summary>
		/// Generates a random number in the range or [Min,Max]
		/// </summary>
		public float NextRange(float Min, float Max)
		{
			return MathHelper.Lerp(Min, Max, (float)this.NextDouble());
		}

		/// <summary>
		/// Generate a random vector about a unit circle
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		public void NextCircleVector(out float x,out float y)
		{
			float Angle = (float)(this.NextDouble() * 2.0 * Math.PI);
			x = (float)Math.Cos(Angle);
			y = (float)Math.Sin(Angle);
		}

		/// <summary>
		/// Generate a normally distributed random number.  Derived from a Wiki reference on
		/// how to do this.
		/// </summary>
		public double NextGaussian(double Mean, double StdDev)
		{
			if (this.UsePrevious)
			{
				this.UsePrevious = false;
				return Mean + y2 * StdDev;
			}
			this.UsePrevious = true;

			double x1 = 0.0;
			double x2 = 0.0;
			double y1 = 0.0;
			double z = 0.0;

			do
			{
				x1 = 2.0 * this.NextDouble() - 1.0;
				x2 = 2.0 * this.NextDouble() - 1.0;
				z = (x1 * x1) + (x2 * x2);
			}
			while (z >= 1.0);

			z = Math.Sqrt((-2.0 * Math.Log(z)) / z);
			y1 = x1 * z;
			y2 = x2 * z;

			return Mean + y1 * StdDev;
		}

		/// <summary>
		/// Keep this around to optimize gaussian calculation performance.
		/// </summary>
		private double y2;
		private bool UsePrevious
		{
			get { return m_UsePrevious; }
			set { m_UsePrevious = value; }
		}
		private bool m_UsePrevious = false;
	}
}
