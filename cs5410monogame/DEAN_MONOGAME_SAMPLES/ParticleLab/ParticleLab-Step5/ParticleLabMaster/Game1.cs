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
        SpriteBatch spriteBatch;
        private SpriteFont m_FrameRateFont;

        private ParticleEmitter m_Emitter1;
        private ParticleEmitter m_Emitter2;
        private ParticleEmitter m_Emitter3;

        private RenderTarget2D m_renderTarget;
        private Rectangle m_rectRenderTexture;
        private Rectangle m_rectRenderTexture2;

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            graphics.IsFullScreen = false;

            this.IsFixedTimeStep = true;
            this.TargetElapsedTime = new TimeSpan(0, 0, 0, 0, 10);
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

            int MiddleX = graphics.GraphicsDevice.Viewport.Width / 2;
            int MiddleY = graphics.GraphicsDevice.Viewport.Height / 2;
            m_Emitter1 = new ParticleEmitter(
                Content,
                new TimeSpan(0, 0, 0, 0, 2),
                MiddleX, MiddleY,
                20,
                140,
                new TimeSpan(0, 0, 4),
                new TimeSpan(0, 0, 0, 0, 3000));

            m_Emitter2 = new ParticleEmitter(
                Content,
                new TimeSpan(0, 0, 0, 0, 25),
                MiddleX, MiddleY,
                40,
                100,
                new TimeSpan(0, 0, 6),
                new TimeSpan(0, 0, 0, 0, 4500));

            m_Emitter3 = new ParticleEmitter(
                Content,
                new TimeSpan(0, 0, 0, 0, 8),
                MiddleX, MiddleY,
                8,
                230,
                new TimeSpan(0, 0, 4),
                new TimeSpan(0, 0, 0));

            m_FrameRateFont = Content.Load<SpriteFont>("FrameRate");

            m_renderTarget = new RenderTarget2D(
                this.graphics.GraphicsDevice,
                this.graphics.GraphicsDevice.PresentationParameters.BackBufferWidth,
                this.graphics.GraphicsDevice.PresentationParameters.BackBufferHeight);

            m_rectRenderTexture = new Rectangle(
                0, 0,
                this.graphics.GraphicsDevice.PresentationParameters.BackBufferWidth / 2,
                this.graphics.GraphicsDevice.PresentationParameters.BackBufferHeight / 2);

            m_rectRenderTexture2 = new Rectangle(
                m_rectRenderTexture.Width,
                m_rectRenderTexture.Height,
                this.graphics.GraphicsDevice.PresentationParameters.BackBufferWidth / 2,
                this.graphics.GraphicsDevice.PresentationParameters.BackBufferHeight / 2);
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
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed ||
                Keyboard.GetState().IsKeyDown(Keys.Escape))
            {
                this.Exit();
            }

            m_Emitter1.Update(gameTime);
            m_Emitter2.Update(gameTime);
            m_Emitter3.Update(gameTime);

            //
            // Check the left thumbstick for movement and let's set the gravity based upon that
            // NOTE : The gravity is not based upon time, it is currently based upon how often
            //        the Update method is called...which isn't a terrific idea in case you were wondering.
            GamePadState State = GamePad.GetState(PlayerIndex.One);
            m_Emitter1.Gravity = new Vector2(State.ThumbSticks.Left.X * 0.02f, -State.ThumbSticks.Left.Y * 0.02f);
            m_Emitter2.Gravity = new Vector2(State.ThumbSticks.Left.X * 0.02f, -State.ThumbSticks.Left.Y * 0.02f);
            m_Emitter3.Gravity = new Vector2(State.ThumbSticks.Left.X * 0.02f, -State.ThumbSticks.Left.Y * 0.02f);

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            graphics.GraphicsDevice.SetRenderTarget(m_renderTarget);
            drawStuff(gameTime);
            graphics.GraphicsDevice.SetRenderTarget(null);

            this.graphics.GraphicsDevice.Clear(Color.CornflowerBlue);

            renderTextureToScreen(m_renderTarget, m_rectRenderTexture);
            renderTextureToScreen(m_renderTarget, m_rectRenderTexture2);

            base.Draw(gameTime);
        }

        private void renderTextureToScreen(RenderTarget2D renderTarget, Rectangle rectRenderTexture)
        {
            this.spriteBatch.Begin();

            this.spriteBatch.Draw(renderTarget, rectRenderTexture, Color.White);

            this.spriteBatch.End();
        }

        private void drawStuff(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);

            //
            // Render the particles
            spriteBatch.Begin(SpriteSortMode.BackToFront, BlendState.Additive);

            m_Emitter1.Draw(spriteBatch);
            m_Emitter2.Draw(spriteBatch);
            m_Emitter3.Draw(spriteBatch);

            spriteBatch.End();

            DisplayFrameRate(gameTime);
        }

        /// <summary>
        /// Just like the man says, Display the Frame Rate
        /// </summary>
        void DisplayFrameRate(GameTime gameTime)
        {
            float FrameRate = 1001.0f;
            if (gameTime.ElapsedGameTime.Milliseconds > 0)
            {
                FrameRate = 1000.0f / gameTime.ElapsedGameTime.Milliseconds;
            }

            string FrameRateString = string.Format("Frames per second: {0:0} Particles: {1}",
                FrameRate, m_Emitter1.ParticleCount + m_Emitter2.ParticleCount + m_Emitter3.ParticleCount);

            spriteBatch.Begin();

            spriteBatch.DrawString(m_FrameRateFont, FrameRateString, new Vector2(65, 65), Color.Black);
            spriteBatch.DrawString(m_FrameRateFont, FrameRateString, new Vector2(64, 64), Color.White);

            spriteBatch.End();
        }
    }
}
