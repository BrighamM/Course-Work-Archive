using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace FontLab
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class Game1 : Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch m_SpriteBatch;
        SpriteFont m_FontArial;
        SpriteFont m_FontComicSans36;
        float m_FontRotation = 0.0f;

        /// <summary>
        /// Define a widescreen standard
        /// </summary>
        private const int WIDESCREEN_WIDTH = 1280;
        private const int WIDESCREEN_HEIGHT = 720;

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            //graphics.PreferredBackBufferWidth = WIDESCREEN_WIDTH;
            //graphics.PreferredBackBufferHeight = WIDESCREEN_HEIGHT;

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
            m_FontArial = Content.Load<SpriteFont>("firstFont");
            m_FontComicSans36 = Content.Load<SpriteFont>("secondFont");
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
            //
            // Check the input devices to see if the user wants to quit
#if XBOX360
			if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
				this.Exit();

#endif

            //
            // If ESC is pressed, exit
#if !XBOX360
            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
            {
                this.Exit();
            }
#endif

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            graphics.GraphicsDevice.Clear(Color.Black);

            m_SpriteBatch.Begin();

            //
            // Standard Demo
            m_SpriteBatch.DrawString(
                m_FontArial,
                m_FontString1,
                new Vector2(0, 0),
                Color.White);

            m_SpriteBatch.DrawString(
               m_FontComicSans36,
               m_FontString2,
               new Vector2(0, m_FontArial.MeasureString(m_FontString1).Y),
               Color.White);

            //
            // Rotate fonts
            m_SpriteBatch.DrawString(
                m_FontArial,
                m_FontString1,
                new Vector2(graphics.GraphicsDevice.Viewport.Width / 2, graphics.GraphicsDevice.Viewport.Height / 2),
                Color.White,
                m_FontRotation += 0.025f,
                //Vector2.Zero,
                new Vector2(m_FontArial.MeasureString(m_FontString1).X / 2, m_FontArial.MeasureString(m_FontString1).Y / 2),
                1.0f,
                SpriteEffects.None,
                0);

            m_SpriteBatch.End();

            base.Draw(gameTime);
        }

        private string m_FontString1 = "The Amazing Font Demo!";
        private string m_FontString2 = "New and improved, now with more pixels...";
    }
}
