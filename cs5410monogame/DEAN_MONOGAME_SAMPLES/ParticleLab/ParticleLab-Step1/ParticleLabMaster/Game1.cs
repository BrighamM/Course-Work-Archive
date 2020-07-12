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
        SpriteBatch spriteBatch;

        private Dictionary<int, Particle> m_particles = new Dictionary<int, Particle>();
        private Texture2D m_texSmoke;
        private Texture2D m_texFire;
        private MyRandom m_random = new MyRandom();

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
            spriteBatch = new SpriteBatch(GraphicsDevice);

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

            List<int> RemoveMe = new List<int>();
            //
            // For any existing particles, update them
            foreach (Particle p in m_particles.Values)
            {
                p.Alive += gameTime.ElapsedGameTime;
                if (p.Alive > p.Lifetime)
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
                m_particles.Remove(Key);
            }

            //
            // Create new particles per frame
            for (int particle = 0; particle < 8; particle++)
            {
                float negX = 1;
                float negY = 1;
                if (m_random.Next(0, 2) == 0) negX = -1;
                if (m_random.Next(0, 2) == 0) negY = -1;
                Vector2 direction = new Vector2((float)(m_random.NextDouble() * negX), (float)(m_random.NextDouble() * negY));
                Particle p = new Particle(
                    m_random.Next(),
                    new Vector2(graphics.GraphicsDevice.Viewport.Width / 2, graphics.GraphicsDevice.Viewport.Height / 2),
                    m_random.nextCircleVector(),
                    //direction,
                    //m_random.Next(1, 4),
                    (float)m_random.nextGaussian(2, 0.5),
                    new TimeSpan(0, 0, 2));

                if (!m_particles.ContainsKey(p.Name))
                {
                    m_particles.Add(p.Name, p);
                }
            }

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);

            //
            // Render the particles
            spriteBatch.Begin();

            TimeSpan switchOver = new TimeSpan(0, 0, 0, 0, 750);
            Texture2D texDraw = m_texFire;
            Rectangle r = new Rectangle(0, 0, 10, 10);
            foreach (Particle p in m_particles.Values)
            {
                if (p.Lifetime > switchOver)
                {
                    texDraw = m_texSmoke;
                }
                else
                {
                    texDraw = m_texFire;
                }

                r.X = (int)p.Position.X;
                r.Y = (int)p.Position.Y;
                spriteBatch.Draw(
                    texDraw,
                    r,
                    null,
                    Color.White,
                    p.Rotation,
                    new Vector2(m_texSmoke.Width / 2, m_texSmoke.Height / 2),
                    SpriteEffects.None,
                    0);
            }

            spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
