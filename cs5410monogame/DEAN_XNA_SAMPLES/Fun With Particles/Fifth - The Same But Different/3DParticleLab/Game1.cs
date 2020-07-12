using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;

namespace ParticleLab
{

	public class Particle
	{
		public Vector3 Center;
		public Vector3 Rotation;
		public float Scale;
		public float Lifetime;
		public Vector3 Delta;
		public Vector3 Tumble;
	}

	public enum fxRenderState
	{
		Diffuse,
		DiffuseSpecular,
		Texture,
		DiffuseTexture,
		DiffuseSpecularTexture,
		PerPixelDiffuseTexture,
		PerPixelDiffuseSpecularTexture
	}
	/// <summary>
	/// This is the main type for your game
	/// </summary>
	public class MagicNumbersAbound : Microsoft.Xna.Framework.Game
	{
		GraphicsDeviceManager graphics;
		SpriteBatch m_SpriteBatch;
		SpriteFont m_SpriteFont;

		private MyInstancedModel m_ModelAsteroid1;
		private MyInstancedModel m_ModelAsteroid2;
		private Texture2D m_txAsteroid1;
		private Texture2D m_txAsteroid2;

		//
		// View and Projection matricies
		private Matrix View
		{
			get { return m_mView; }
		}
		private Matrix m_mView;

		private Matrix Projection
		{
			get { return m_mProjection; }
		}
		private Matrix m_mProjection;

		/// <summary>
		/// A container for all the particles in the "explosion"
		/// </summary>
		private List<Particle> Particles1
		{
			get { return m_Particles1; }
		}
		private List<Particle> m_Particles1;

		private List<Particle> Particles2
		{
			get { return m_Particles2; }
		}
		private List<Particle> m_Particles2;
		private const int COUNT_PARTICLES = 500;

		//
		// Framerate stuff
		private int m_FrameRate;
		private int m_FrameCount;
		private TimeSpan m_ElapsedTime;

		//
		// The effects we'll use to render the particles
		private List<Effect> m_fxParticles = new List<Effect>();
		
		/// <summary>
		/// Tracks which effect is currently in use
		/// </summary>
		private fxRenderState CurrentEffect
		{
			get { return m_CurrentEffect; }
			set { m_CurrentEffect = value; }
		}
		private fxRenderState m_CurrentEffect = fxRenderState.Diffuse;

		public MagicNumbersAbound()
		{
			graphics = new GraphicsDeviceManager(this);
			Content.RootDirectory = "Content";

			//
			// This releases the 60 fps cap, so we can test for performance
			IsFixedTimeStep = false;
			graphics.SynchronizeWithVerticalRetrace = false;
		}

		/// <summary>
		/// Allows the game to perform any initialization it needs to before starting to run.
		/// This is where it can query for any required services and load any non-graphic
		/// related content.  Calling base.Initialize will enumerate through any components
		/// and initialize them as well.
		/// </summary>
		protected override void Initialize()
		{
			m_mView = Matrix.CreateLookAt(new Vector3(0.0f, 0.0f, 5000.0f), Vector3.Zero, Vector3.Up);

			//
			// Ensure that circles look like circles, not squares.  Meaning, we have to manually
			// fiddle with the aspect ratio ourselves.
			float Scale = graphics.GraphicsDevice.Viewport.AspectRatio;
			m_mProjection = Matrix.CreateOrthographicOffCenter(-5000 * Scale, 5000 * Scale, -5000, 5000, 1.0f, 10000.0f);

			base.Initialize();
		}

		/// <summary>
		/// LoadContent will be called once per game and is the place to load
		/// all of your content.
		/// </summary>
		protected override void LoadContent()
		{
			m_SpriteBatch = new SpriteBatch(graphics.GraphicsDevice);
			m_SpriteFont = Content.Load<SpriteFont>("FrameRate");

			m_ModelAsteroid1 = new MyInstancedModel(graphics.GraphicsDevice, Content.Load<Model>(@"Models\Asteroid1"), COUNT_PARTICLES);
			m_ModelAsteroid2 = new MyInstancedModel(graphics.GraphicsDevice, Content.Load<Model>(@"Models\Asteroid2"), COUNT_PARTICLES);

			m_txAsteroid1 = Content.Load<Texture2D>(@"Textures\Asteroid1");
			m_txAsteroid2 = Content.Load<Texture2D>(@"Textures\Asteroid2");

			m_fxParticles.Add(Content.Load<Effect>(@"Effects\Diffuse"));
			m_fxParticles.Add(Content.Load<Effect>(@"Effects\DiffuseSpecular"));
			m_fxParticles.Add(Content.Load<Effect>(@"Effects\Texture"));
			m_fxParticles.Add(Content.Load<Effect>(@"Effects\DiffuseTexture"));
			m_fxParticles.Add(Content.Load<Effect>(@"Effects\DiffuseSpecularTexture"));
			m_fxParticles.Add(Content.Load<Effect>(@"Effects\PerPixelDiffuseTexture"));
			m_fxParticles.Add(Content.Load<Effect>(@"Effects\PerPixelDiffuseSpecularTexture"));

			//
			// Create a bunch of particles
			InitParticles();
		}

		/// <summary>
		/// Gets the different sets of particles built up for us.
		/// </summary>
		private void InitParticles()
		{
			m_Particles1 = new List<Particle>(COUNT_PARTICLES);
			m_Particles2 = new List<Particle>(COUNT_PARTICLES);
			MyRandom rnd = new MyRandom();
			GenerateParticles(rnd, m_Particles1);
			GenerateParticles(rnd, m_Particles2);
		}

		/// <summary>
		/// Do what the man says, make some new particles
		/// </summary>
		/// <param name="rnd"></param>
		/// <param name="vParticles"></param>
		private void GenerateParticles(MyRandom rnd, List<Particle> vParticles)
		{
			for (int Particle = 0; Particle < COUNT_PARTICLES; Particle++)
			{
				Particle NewParticle = new Particle();
				NewParticle.Scale = rnd.NextRange(0.05f, 0.15f);

				NewParticle.Center = Vector3.Zero;
				//
				// Choose a delta, then a point on a circle and create a vector in that direction.
				float Delta = (float)rnd.NextGaussian(5.0, 10.0);
				float x, y;
				rnd.NextCircleVector(out x, out y);
				NewParticle.Delta = new Vector3(Delta * x, Delta * y, 0.0f);

				NewParticle.Rotation = Vector3.Zero;
				NewParticle.Tumble = new Vector3((float)rnd.NextDouble() / 10.0f, (float)rnd.NextDouble() / 10.0f, (float)rnd.NextDouble() / 10.0f);

				vParticles.Add(NewParticle);
			}
		}

		/// <summary>
		/// UnloadContent will be called once per game and is the place to unload
		/// all content.
		/// </summary>
		protected override void UnloadContent()
		{
			// TODO: Unload any non ContentManager content here
		}

		/// <summary>
		/// Allows the game to run logic such as updating the world,
		/// checking for collisions, gathering input, and playing audio.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Update(GameTime gameTime)
		{
			// Allows the game to exit
			if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
				this.Exit();

			//
			// Check to see if the user wants to try a different effect
			if (Keyboard.GetState().IsKeyDown(Keys.F1))
			{
				this.CurrentEffect = fxRenderState.Diffuse;
			}
			else if (Keyboard.GetState().IsKeyDown(Keys.F2))
			{
				this.CurrentEffect = fxRenderState.DiffuseSpecular;
			}
			else if (Keyboard.GetState().IsKeyDown(Keys.F3))
			{
				this.CurrentEffect = fxRenderState.Texture;
			}
			else if (Keyboard.GetState().IsKeyDown(Keys.F4))
			{
				this.CurrentEffect = fxRenderState.DiffuseTexture;
			}
			else if (Keyboard.GetState().IsKeyDown(Keys.F5))
			{
				this.CurrentEffect = fxRenderState.DiffuseSpecularTexture;
			}
			else if (Keyboard.GetState().IsKeyDown(Keys.F6))
			{
				this.CurrentEffect = fxRenderState.PerPixelDiffuseTexture;
			}
			else if (Keyboard.GetState().IsKeyDown(Keys.F7))
			{
				this.CurrentEffect = fxRenderState.PerPixelDiffuseSpecularTexture;
			}

			//
			// Move the positions and update the rotations of the particles
			foreach (Particle p in this.Particles1)
			{
				p.Center.X += p.Delta.X;
				p.Center.Y += p.Delta.Y;

				p.Rotation.X += p.Tumble.X;
				p.Rotation.Y += p.Tumble.Y;
				p.Rotation.Z += p.Tumble.Z;
			}

			foreach (Particle p in this.Particles2)
			{
				p.Center.X += p.Delta.X;
				p.Center.Y += p.Delta.Y;

				p.Rotation.X += p.Tumble.X;
				p.Rotation.Y += p.Tumble.Y;
				p.Rotation.Z += p.Tumble.Z;
			}

			//
			// Compute the framerate
			m_ElapsedTime += gameTime.ElapsedGameTime;

			if (m_ElapsedTime > TimeSpan.FromSeconds(1))
			{
				m_ElapsedTime -= TimeSpan.FromSeconds(1);
				m_FrameRate = m_FrameCount;
				m_FrameCount = 0;
			}

			base.Update(gameTime);
		}

		/// <summary>
		/// This is the next step in increasing the performance of drawing objects.  If we know
		/// the objects are all to be the same, we can reuse the same index, vertex buffer decls
		/// and only change the transformation matrices as we need them.
		/// </summary>
		/// <param name="gameTime"></param>
		protected override void Draw(GameTime gameTime)
		{
			graphics.GraphicsDevice.Clear(Color.CornflowerBlue);

			//
			// The sprite batch makes a little mess of things, so have to set some render states back
			graphics.GraphicsDevice.RenderState.DepthBufferEnable = true;
			graphics.GraphicsDevice.RenderState.AlphaBlendEnable = false;
			graphics.GraphicsDevice.RenderState.AlphaTestEnable = false;

			//
			// Draw each particle that uses the first texture
			for (int Particle = 0; Particle < this.Particles1.Count; Particle++)
			{
				Matrix mRotation =
					Matrix.CreateRotationX(this.Particles1[Particle].Rotation.X) *
					Matrix.CreateRotationY(this.Particles1[Particle].Rotation.Y) *
					Matrix.CreateRotationZ(this.Particles1[Particle].Rotation.Z);

				Matrix mTransform =
					mRotation *
					Matrix.CreateScale(this.Particles1[Particle].Scale) *
					Matrix.CreateTranslation(this.Particles1[Particle].Center);

				m_ModelAsteroid1.Draw(mTransform, mRotation);
			}

			//
			// Update the effect and flush the draw calls for display
			m_fxParticles[(int)m_CurrentEffect].Parameters["Texture"].SetValue(m_txAsteroid1);
			m_ModelAsteroid1.Flush(graphics.GraphicsDevice, m_fxParticles[(int)m_CurrentEffect], m_mView, m_mProjection);

			//
			// Do the same for the second particle type
			for (int Particle = 0; Particle < this.Particles2.Count; Particle++)
			{
				Matrix mRotation =
					Matrix.CreateRotationX(this.Particles2[Particle].Rotation.X) *
					Matrix.CreateRotationY(this.Particles2[Particle].Rotation.Y) *
					Matrix.CreateRotationZ(this.Particles2[Particle].Rotation.Z);

				Matrix mTransform =
					mRotation *
					Matrix.CreateScale(this.Particles2[Particle].Scale) *
					Matrix.CreateTranslation(this.Particles2[Particle].Center);

				m_ModelAsteroid2.Draw(mTransform, mRotation);
			}

			//
			// Update the effect and flush the draw calls for display
			m_fxParticles[(int)m_CurrentEffect].Parameters["Texture"].SetValue(m_txAsteroid2);
			m_ModelAsteroid2.Flush(graphics.GraphicsDevice, m_fxParticles[(int)m_CurrentEffect], m_mView, m_mProjection);

			DisplayFrameRate();

			m_FrameCount++;

			base.Draw(gameTime);
		}

		/// <summary>
		/// Just like the man says, Display the Frame Rate
		/// </summary>
		void DisplayFrameRate()
		{
			string FrameRate = string.Format("Frames per second: {0}\n", m_FrameRate);

			m_SpriteBatch.Begin();

			m_SpriteBatch.DrawString(m_SpriteFont, FrameRate, new Vector2(65, 65), Color.Black);
			m_SpriteBatch.DrawString(m_SpriteFont, FrameRate, new Vector2(64, 64), Color.White);

			m_SpriteBatch.DrawString(m_SpriteFont, this.CurrentEffect.ToString(), new Vector2(65, 20), Color.Black);
			m_SpriteBatch.DrawString(m_SpriteFont, this.CurrentEffect.ToString(), new Vector2(64, 19), Color.White);

			m_SpriteBatch.End();
		}
	}
}
