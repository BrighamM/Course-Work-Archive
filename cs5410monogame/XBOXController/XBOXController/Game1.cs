using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace XBOXController
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class Game1 : Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        private Texture2D background;
        private Texture2D redDot;
        private Texture2D greenDot;
        private Texture2D blueDot;
        private SpriteFont controllerFont;

        GamePadState gamePadState;



        bool gamePadIsConnected;
        bool xButtonIsPressed;
        bool aButtonIsPressed;
        bool yButtonIsPressed;
        bool bButtonIsPressed;
        bool startButtonIsPressed;
        bool backButtonIsPressed;
        bool rightShoulderIsPressed;
        bool leftShoulderIsPressed;
        bool bigButtonIsPressed;
        bool leftStickButtonIsPressed;
        bool rightStickButtonIsPressed;

        bool dPadUpIsPressed;
        bool dPadDownIsPressed;
        bool dPadLeftIsPressed;
        bool dPadRightIsPressed;

        bool leftStickMoving;
        bool rightStickMoving;
        bool leftTriggerMoving;
        bool rightTriggerMoving;

        float leftStickX;
        float leftStickY;
        float rightStickX;
        float rightStickY;

        float leftTrigger;
        float rightTrigger;

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


            gamePadState = GamePad.GetState(PlayerIndex.One);
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);
            background = Content.Load<Texture2D>("ControllerPic/controller");
            controllerFont = Content.Load<SpriteFont>("ControllerFont/controllerFont");
            redDot = Content.Load<Texture2D>("RGBColors/red");
            greenDot = Content.Load<Texture2D>("RGBColors/green");
            blueDot = Content.Load<Texture2D>("RGBColors/blue");

            // TODO: use this.Content to load your game content here
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// game-specific content.
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
            //if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
            //    Exit();

            gamePadState = GamePad.GetState(PlayerIndex.One);



            if (gamePadState.IsConnected)
            {
                gamePadIsConnected = true;
            }
            else
            {
                gamePadIsConnected = false;
            }

            if (gamePadState.Buttons.X == ButtonState.Pressed)
            {
                xButtonIsPressed = true;
            }
            else
            {
                xButtonIsPressed = false;
            }

            if (gamePadState.Buttons.Y == ButtonState.Pressed)
            {
                yButtonIsPressed = true;
            }
            else
            {
                yButtonIsPressed = false;
            }

            if (gamePadState.Buttons.B == ButtonState.Pressed)
            {
                bButtonIsPressed = true;
            }
            else
            {
                bButtonIsPressed = false;
            }

            if (gamePadState.Buttons.A == ButtonState.Pressed)
            {
                aButtonIsPressed = true;
            }
            else
            {
                aButtonIsPressed = false;
            }

            if (gamePadState.Buttons.Back == ButtonState.Pressed)
            {
                backButtonIsPressed = true;
            }
            else
            {
                backButtonIsPressed = false;
            }

            if (gamePadState.Buttons.Start == ButtonState.Pressed)
            {
                startButtonIsPressed = true;
            }
            else
            {
                startButtonIsPressed = false;
            }
            

            if (gamePadState.Buttons.RightShoulder == ButtonState.Pressed)
            {
                rightShoulderIsPressed = true;
            }
            else
            {
                rightShoulderIsPressed = false;
            }

            if (gamePadState.Buttons.LeftShoulder == ButtonState.Pressed)
            {
                leftShoulderIsPressed = true;
            }
            else
            {
                leftShoulderIsPressed = false;
            }

            if (gamePadState.Buttons.BigButton == ButtonState.Pressed)
            {
                bigButtonIsPressed = true;
            }
            else
            {
                bigButtonIsPressed = false;
            }

            if (gamePadState.Buttons.RightStick == ButtonState.Pressed)
            {
                rightStickButtonIsPressed = true;
                GamePad.SetVibration(PlayerIndex.One, 0.0f, 1.0f);
            }
            else
            {
                rightStickButtonIsPressed = false;
                GamePad.SetVibration(PlayerIndex.One, 0.0f, 0.0f);
            }
            if (gamePadState.Buttons.LeftStick == ButtonState.Pressed)
            {
                leftStickButtonIsPressed = true;
                GamePad.SetVibration(PlayerIndex.One, 1.0f, 0.0f);
            }
            else
            {
                leftStickButtonIsPressed = false;
                GamePad.SetVibration(PlayerIndex.One, 0.0f, 0.0f);
            }



            if (gamePadState.DPad.Up == ButtonState.Pressed)
            {
                dPadUpIsPressed = true;
            }
            else
            {
                dPadUpIsPressed = false;
            }
            if (gamePadState.DPad.Down == ButtonState.Pressed)
            {
                dPadDownIsPressed = true;
            }
            else
            {
                dPadDownIsPressed = false;
            }
            if (gamePadState.DPad.Left == ButtonState.Pressed)
            {
                dPadLeftIsPressed = true;
            }
            else
            {
                dPadLeftIsPressed = false;
            }
            if (gamePadState.DPad.Right == ButtonState.Pressed)
            {
                dPadRightIsPressed = true;
            }
            else
            {
                dPadRightIsPressed = false;
            }


            leftStickX = gamePadState.ThumbSticks.Left.X;
            leftStickY = gamePadState.ThumbSticks.Left.Y;
            rightStickX = gamePadState.ThumbSticks.Right.X;
            rightStickY = gamePadState.ThumbSticks.Right.Y;

            rightTrigger = gamePadState.Triggers.Right;
            leftTrigger = gamePadState.Triggers.Left;


            // TODO: Add your update logic here

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            spriteBatch.Begin();

            spriteBatch.Draw(background, new Rectangle(0, 0, 800, 480), Color.White);
            if (gamePadIsConnected)
            {
                spriteBatch.DrawString(controllerFont, "GAMEPAD IS CONNECTED! ", new Vector2(0, 0), Color.Green);
            }

            spriteBatch.DrawString(controllerFont, "L-TRIGGER VAL: " + leftTrigger.ToString(), new Vector2(0, 33), Color.Black);
            spriteBatch.DrawString(controllerFont, "R-TRIGGER VAL: " + rightTrigger.ToString(), new Vector2(0, 66), Color.Black);
            spriteBatch.DrawString(controllerFont, "L-STICK X-VAL: " + leftStickX.ToString(), new Vector2(0, 100), Color.Black);
            spriteBatch.DrawString(controllerFont, "L-STICK Y-VAL: " + leftStickY.ToString(), new Vector2(0, 133), Color.Black);
            spriteBatch.DrawString(controllerFont, "R-STICK X-VAL: " + rightStickX.ToString(), new Vector2(0, 166), Color.Black);
            spriteBatch.DrawString(controllerFont, "R-STICK Y-VAL: " + rightStickY.ToString(), new Vector2(0, 200), Color.Black);


            spriteBatch.End();

            spriteBatch.Begin(SpriteSortMode.Immediate, BlendState.Additive);

            if (xButtonIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(500, 220, 50, 50), Color.White);
            }
            if (yButtonIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(550, 170, 50, 50), Color.White);
            }
            if (bButtonIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(590, 210, 50, 50), Color.White);
            }
            if (aButtonIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(540, 260, 50, 50), Color.White);
            }
            if (backButtonIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(315, 215, 50, 50), Color.White);
            }
            if (startButtonIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(435, 220, 50, 50), Color.White);
            }

            if (leftShoulderIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(170, 100, 50, 50), Color.White);
            }
            if (rightShoulderIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(580, 100, 50, 50), Color.White);
            }
            if (bigButtonIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(350, 200, 100, 100), Color.White);
            }

            if (leftStickButtonIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(175, 215, 100, 100), Color.White);
            }
            if (rightStickButtonIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(430, 308, 100, 100), Color.White);
            }

            if (dPadUpIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(288, 290, 50, 50), Color.White);
            }
            if (dPadDownIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(288, 350, 50, 50), Color.White);
            }
            if (dPadLeftIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(255, 320, 50, 50), Color.White);
            }
            if (dPadRightIsPressed)
            {
                spriteBatch.Draw(greenDot, new Rectangle(315, 320, 50, 50), Color.White);
            }


            spriteBatch.End();

            // TODO: Add your drawing code here

            base.Draw(gameTime);
        }
    }
}
