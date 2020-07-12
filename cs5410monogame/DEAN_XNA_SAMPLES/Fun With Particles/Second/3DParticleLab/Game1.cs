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
		public Model Model;
		public Texture2D Texture;
		public Vector3 Center;
		public Vector3 Rotation;
		public float Scale;
		public float Lifetime;
		public Vector3 Delta;
		public Vector3 Tumble;
	}
	/// <summary>
	/// This is the main type for your game
	/// </summary>
	public class MagicNumbersAbound : Microsoft.Xna.Framework.Game
	{
		GraphicsDeviceManager graphics;
		SpriteBatch m_SpriteBatch;
		SpriteFont m_SpriteFont;

		private List<Model> m_Models = new List<Model>();
		private List<Texture2D> m_Textures = new List<Texture2D>();

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
		private List<Particle> Particles
		{
			get { return m_Particles; }
		}
		private List<Particle> m_Particles;
		private const int COUNT_PARTICLES = 1000;

		//
		// Framerate stuff
		private int m_FrameRate;
		private int m_FrameCount;
		private TimeSpan m_ElapsedTime;

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

			m_Models.Add(Content.Load<Model>(@"Models\Asteroid1"));
			m_Models.Add(Content.Load<Model>(@"Models\Asteroid2"));

			m_Textures.Add(Content.Load<Texture2D>(@"Textures\Asteroid1"));
			m_Textures.Add(Content.Load<Texture2D>(@"Textures\Asteroid2"));

			//
			// Create a bunch of particles
			MyRandom rnd = new MyRandom();
			m_Particles = new List<Particle>(COUNT_PARTICLES);
			for (int Particle = 0; Particle < COUNT_PARTICLES; Particle++)
			{
				Particle NewParticle = new Particle();
				NewParticle.Model = m_Models[0]; // m_Models[rnd.Next(m_Models.Count)];
				NewParticle.Texture = m_Textures[rnd.Next(m_Models.Count)];
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

				this.Particles.Add(NewParticle);
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
			// Move the positions and update the rotations of the particles
			for (int Item=0; Item<COUNT_PARTICLES; Item++)
			{
				this.Particles[Item].Center += this.Particles[Item].Delta;
				this.Particles[Item].Rotation += this.Particles[Item].Tumble;
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
		/// This is a more efficient rendering technique for the particles.  It eliminates
		/// the state changes and a ton of needless computations.  Rough estimate that it is 50% 
		/// faster than the above code.
		/// </summary>
		protected override void Draw(GameTime gameTime)
		{
			graphics.GraphicsDevice.Clear(Color.CornflowerBlue);

            //
            // The sprite batch makes a little mess of things, so have to set some render states back
            DepthStencilState depthStencilState = new DepthStencilState();
            depthStencilState.DepthBufferEnable = true;
            depthStencilState.DepthBufferWriteEnable = true;
            graphics.GraphicsDevice.DepthStencilState = depthStencilState;
            graphics.GraphicsDevice.BlendState = BlendState.Opaque;

			//
			// We know the effect is the same for all particles, so just the effect from the first particle
			BasicEffect effect = (BasicEffect)this.Particles[0].Model.Meshes[0].Effects[0];
			effect.EnableDefaultLighting();
			effect.View = m_mView;
			effect.Projection = m_mProjection;

			//
			// Draw all our particles
			foreach (Particle p in this.Particles)
			{
				DrawModel(p.Model, effect, p.Texture, p.Rotation, p.Center, p.Scale);
			}

			DisplayFrameRate();

			m_FrameCount++;

			base.Draw(gameTime);
		}

		/// <summary>
		/// Related DrawModel method that improves rendering performance.
		/// </summary>
		private void DrawModel(Model DrawMe, BasicEffect effect, Texture2D Texture, Vector3 Rotation, Vector3 Position, float Scale)
		{
			//
			// Draw the model. A model can have multiple meshes, so loop.
			foreach (ModelMesh Mesh in DrawMe.Meshes)
			{
				effect.Texture = Texture;
				effect.World =
					Matrix.CreateRotationX(Rotation.X) *
					Matrix.CreateRotationY(Rotation.Y) *
					Matrix.CreateRotationZ(Rotation.Z) *
					Matrix.CreateScale(Scale) *
					Matrix.CreateTranslation(Position);

				//
				// Draw the beast!
				Mesh.Draw();
			}
		}

		void DisplayFrameRate()
		{
			string FrameRate = string.Format("Frames per second: {0}\n", m_FrameRate);

			m_SpriteBatch.Begin();

			m_SpriteBatch.DrawString(m_SpriteFont, FrameRate, new Vector2(65, 65), Color.Black);
			m_SpriteBatch.DrawString(m_SpriteFont, FrameRate, new Vector2(64, 64), Color.White);

			m_SpriteBatch.End();
		}
	}
}
