using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

using System;
using InputLab.Input;

namespace GameInputOption3
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class Game1 : Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        private Rectangle m_titleSafeArea;
        private Rectangle m_spriteArea;
        private Texture2D m_texSessler;
        private IInputDevice m_inputKeyboard;
        private IInputDevice m_inputController;

        /// <summary>
        /// Define a widescreen standard
        /// </summary>
        private const int WIDESCREEN_WIDTH = 1280;
        private const int WIDESCREEN_HEIGHT = 720;
        /// <summary>
        /// These describe the different states the sprite might be in as it moves around the screen
        /// </summary>
        private enum SpriteState { TopRight, RightDown, DownLeft, LeftUp }
        /// <summary>
        /// How fast the sprite moves in pixels/second
        /// </summary>
        private const int SPRITE_SPEED = 500;
        /// <summary>
        /// Size of border to reserve for the "Title Safe Area", as a fraction from 0.0 to 1.0
        /// </summary>
        private const double TitleSafeBorder = 0.20;

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            this.IsFixedTimeStep = false;   // Force an update call as often as possible

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
            //
            // Prepare the title safe area
            m_titleSafeArea = buildTitleSafeArea(1.0 - Game1.TitleSafeBorder);

            //
            // Prepare the basic rectangle size for the sprite
            m_spriteArea = buildSpriteArea();

            //
            // Setup input handlers
            m_inputController = new GamePadInput(PlayerIndex.One);

            m_inputController.registerCommand(Buttons.LeftThumbstickUp, false, new InputDeviceHelper.CommandDelegate(handlerMoveUp));
            m_inputController.registerCommand(Buttons.LeftThumbstickDown, false, new InputDeviceHelper.CommandDelegate(handlerMoveDown));
            m_inputController.registerCommand(Buttons.LeftThumbstickLeft, false, new InputDeviceHelper.CommandDelegate(handlerMoveLeft));
            m_inputController.registerCommand(Buttons.LeftThumbstickRight, false, new InputDeviceHelper.CommandDelegate(handlerMoveRight));

            m_inputKeyboard = new KeyboardInput();

            m_inputKeyboard.registerCommand(Keys.W, false, new InputDeviceHelper.CommandDelegate(handlerMoveUp));
            m_inputKeyboard.registerCommand(Keys.S, false, new InputDeviceHelper.CommandDelegate(handlerMoveDown));
            m_inputKeyboard.registerCommand(Keys.A, false, new InputDeviceHelper.CommandDelegate(handlerMoveLeft));
            m_inputKeyboard.registerCommand(Keys.D, false, new InputDeviceHelper.CommandDelegate(handlerMoveRight));

            m_inputKeyboard.registerCommand(Keys.Up, false, new InputDeviceHelper.CommandDelegate(handlerMoveUp));
            m_inputKeyboard.registerCommand(Keys.Down, false, new InputDeviceHelper.CommandDelegate(handlerMoveDown));
            m_inputKeyboard.registerCommand(Keys.Left, false, new InputDeviceHelper.CommandDelegate(handlerMoveLeft));
            m_inputKeyboard.registerCommand(Keys.Right, false, new InputDeviceHelper.CommandDelegate(handlerMoveRight));

            base.Initialize();
        }

        #region Input Callbacks

        public void handlerMoveUp(GameTime gameTime, float value)
        {
            //
            // Compute how many pixels to acutally move
            double seconds = gameTime.ElapsedGameTime.TotalMilliseconds / 1000.0;
            int moveDistance = (int)((seconds * SPRITE_SPEED) * value);

            if (m_spriteArea.Y > 0)
            {
                m_spriteArea.Y = Math.Max(m_spriteArea.Y - moveDistance, 0);
            }
        }

        public void handlerMoveDown(GameTime gameTime, float value)
        {
            //
            // Compute how many pixels to acutally move
            double seconds = gameTime.ElapsedGameTime.TotalMilliseconds / 1000.0;
            int moveDistance = (int)((seconds * SPRITE_SPEED) * value);

            if ((m_spriteArea.Y + moveDistance + m_spriteArea.Height) < (m_titleSafeArea.Y + m_titleSafeArea.Height))
            {
                m_spriteArea.Y += moveDistance;
            }
        }

        public void handlerMoveLeft(GameTime gameTime, float value)
        {
            //
            // Compute how many pixels to acutally move
            double seconds = gameTime.ElapsedGameTime.TotalMilliseconds / 1000.0;
            int moveDistance = (int)((seconds * SPRITE_SPEED) * value);

            if (m_spriteArea.X > 0)
            {
                m_spriteArea.X = Math.Max(m_spriteArea.X - moveDistance, 0);
            }
        }

        public void handlerMoveRight(GameTime gameTime, float value)
        {
            //
            // Compute how many pixels to acutally move
            double seconds = gameTime.ElapsedGameTime.TotalMilliseconds / 1000.0;
            int moveDistance = (int)((seconds * SPRITE_SPEED) * value);

            if ((m_spriteArea.X + m_spriteArea.Width) < (m_titleSafeArea.X + m_titleSafeArea.Width))
            {
                m_spriteArea.X += moveDistance;
            }
        }

        #endregion

        /// <summary>
        /// Prepares a Rectangle that describes the "safe" area of the screen to draw
        /// into...because not all TV's show the full screen properly.
        /// </summary>
        /// <returns></returns>
        private Rectangle buildTitleSafeArea(double percent)
        {
            Rectangle area = new Rectangle(
                this.graphics.GraphicsDevice.Viewport.X,
                this.graphics.GraphicsDevice.Viewport.Y,
                this.graphics.GraphicsDevice.Viewport.Width,
                this.graphics.GraphicsDevice.Viewport.Height);

#if XBOX360
			double Border = (1.0 - Percent)/2.0;
			Area.X = (int)(Border * Area.Width);
			Area.Y = (int)(Border * Area.Height);
			Area.Width = (int)(Percent * Area.Width);
			Area.Height = (int)(Percent * Area.Height);
#endif

            return area;
        }

        /// <summary>
        /// Constructs the basic area the sprite will cover.  This ignores whatever the
        /// size of the sprite is, we are forcing it into a specific size.
        /// 
        /// The intention is that the game update will position the sprite based upon
        /// elapsed time.
        /// </summary>
        /// <returns></returns>
        private Rectangle buildSpriteArea()
        {
            return new Rectangle(0, 0, 300, 300);
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);

            //
            // Load our pretty picture
            m_texSessler = Content.Load<Texture2D>("Sessler");

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
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
            {
                this.Exit();
            }
            //
            // If ESC is pressed, exit
            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
            {
                this.Exit();
            }

            m_inputKeyboard.Update(gameTime);
            m_inputController.Update(gameTime);

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            graphics.GraphicsDevice.Clear(Color.CornflowerBlue);

            //
            // This is the simplest example of getting sprites drawn
            spriteBatch.Begin();

            spriteBatch.Draw(m_texSessler, m_spriteArea, Color.White);

            spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
