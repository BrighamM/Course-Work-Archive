using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

using System;
using System.Collections.Generic;

namespace ParticleLabMaster
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class Game1 : Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch m_SpriteBatch;

        public class Particle
        {
            public Particle(int Name, Vector2 Position, Vector2 Direction, float Speed, TimeSpan Lifetime)
            {
                this.Name = Name;
                this.Position = Position;
                this.Direction = Direction;
                this.Speed = Speed;
                this.Lifetime = Lifetime;

                this.Rotation = 0;
            }

            public int Name;
            public Vector2 Position;
            public float Rotation;
            public Vector2 Direction;
            public float Speed;
            public TimeSpan Lifetime;
        }

        private Dictionary<int, Particle> m_Particles = new Dictionary<int, Particle>();
        private Texture2D m_texSmoke;
        private Texture2D m_texFire;
        private MyRandom m_Random = new MyRandom();

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            m_SpriteBatch = new SpriteBatch(GraphicsDevice);

            m_texSmoke = Content.Load<Texture2D>("Smoke");
            m_texFire = Content.Load<Texture2D>("Fire");
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
            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
            {
                this.Exit();
            }

            //
            // Generate some new particles
            for (int particle = 0; particle < 4; particle++)
            {
                Particle p = new Particle(
                    m_Random.Next(),
                    new Vector2(graphics.GraphicsDevice.Viewport.Width / 2, graphics.GraphicsDevice.Viewport.Height / 2),
                    m_Random.NextCircleVector(),
                    (float)m_Random.NextGaussian(2, 1),
                    new TimeSpan(0, 0, 4));

                if (!m_Particles.ContainsKey(p.Name))
                {
                    m_Particles.Add(p.Name, p);
                }
            }

            List<int> RemoveMe = new List<int>();
            //
            // For any existing particles, update them
            foreach (Particle p in m_Particles.Values)
            {
                p.Lifetime -= gameTime.ElapsedGameTime;
                if (p.Lifetime < TimeSpan.Zero)
                {
                    //
                    // Add to the remove list
                    RemoveMe.Add(p.Name);
                }
                //
                // Update its position
                p.Position += (p.Direction * p.Speed);
                //
                // Have it rotate proportional to its speed
                p.Rotation += p.Speed / 50.0f;
            }

            foreach (int Key in RemoveMe)
            {
                m_Particles.Remove(Key);
            }

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            //
            // Render the particles
            m_SpriteBatch.Begin(SpriteSortMode.BackToFront, BlendState.Additive);

            Rectangle r = new Rectangle(0, 0, 20, 20);
            foreach (Particle p in m_Particles.Values)
            {
                Texture2D texDraw;
                if (p.Lifetime < new TimeSpan(0, 0, 0, 0, 3500))
                {
                    texDraw = m_texSmoke;
                }
                else
                {
                    texDraw = m_texFire;
                }

                r.X = (int)p.Position.X;
                r.Y = (int)p.Position.Y;
                m_SpriteBatch.Draw(
                    texDraw,
                    r,
                    null,
                    Color.White,
                    p.Rotation,
                    new Vector2(m_texSmoke.Width / 2, m_texSmoke.Height / 2),
                    SpriteEffects.None,
                    0);
            }

            m_SpriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
