using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

using System;
using ParticleLab.Particles;

namespace ParticleLabMaster
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class Game1 : Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch m_SpriteBatch;

        ParticleEmitter m_Emitter1;
        ParticleEmitter m_Emitter2;
        ParticleEmitter m_Emitter3;


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

            int MiddleX = graphics.GraphicsDevice.Viewport.Width / 2;
            int MiddleY = graphics.GraphicsDevice.Viewport.Height / 2;
            m_Emitter1 = new ParticleEmitter(
                Content,
                new TimeSpan(0, 0, 0, 0, 5),
                MiddleX, MiddleY,
                20,
                2,
                new TimeSpan(0, 0, 4),
                new TimeSpan(0, 0, 0, 0, 3000));

            m_Emitter2 = new ParticleEmitter(
                Content,
                new TimeSpan(0, 0, 0, 0, 25),
                MiddleX, MiddleY,
                40,
                1,
                new TimeSpan(0, 0, 6),
                new TimeSpan(0, 0, 0, 0, 5000));

            m_Emitter3 = new ParticleEmitter(
                Content,
                new TimeSpan(0, 0, 0, 0, 10),
                MiddleX, MiddleY,
                8,
                4,
                new TimeSpan(0, 0, 4),
                new TimeSpan(0, 0, 0));
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

            m_Emitter1.Update(gameTime);
            m_Emitter2.Update(gameTime);
            m_Emitter3.Update(gameTime);


            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.DarkGray);

            //
            // Render the particles
            m_SpriteBatch.Begin(SpriteSortMode.BackToFront, BlendState.Additive);

            m_Emitter1.Draw(m_SpriteBatch);
            m_Emitter2.Draw(m_SpriteBatch);
            m_Emitter3.Draw(m_SpriteBatch);

            m_SpriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
