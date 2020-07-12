using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace SpriteLab1_monogame
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class Game1 : Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        /// <summary>
        /// Our texture stuff
        /// </summary>
        private Texture2D m_texSessler;
        private Rectangle m_rectSessler;

        /// <summary>
        /// How fast the sprite moves in pixels/second
        /// </summary>
        private const int SPRITE_SPEED = 300;

        public Game1()
        {
            this.graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";

            //this.IsFixedTimeStep = true;
            //this.TargetElapsedTime = new TimeSpan(0, 0, 0, 0, 100);

            //m_graphics.PreferredBackBufferWidth = 1024;
            //m_graphics.PreferredBackBufferHeight = 768;


            //this.m_graphics.IsFullScreen = true;
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
            this.spriteBatch = new SpriteBatch(GraphicsDevice);

            //
            // Load our pretty picture
            m_texSessler = this.Content.Load<Texture2D>("Sessler");

            //
            // Define the initial size and area we want the texture to take up
            m_rectSessler = new Rectangle(0, 0, 200, 200);
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
            {
                this.Exit();
            }

            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
            {
                this.Exit();
            }

            //
            // Compute how many pixels to acutally move
            double seconds = gameTime.ElapsedGameTime.TotalSeconds;
            int moveDistance = (int)(seconds * SPRITE_SPEED);

            foreach (Keys Key in Keyboard.GetState().GetPressedKeys())
            {
                MoveOnKey(Key, moveDistance);
            }

            if (GamePad.GetState(PlayerIndex.One).Buttons.A == ButtonState.Pressed)
            {
                MoveDown(moveDistance);
            }
            if (GamePad.GetState(PlayerIndex.One).Buttons.B == ButtonState.Pressed)
            {
                MoveRight(moveDistance);
            }
            if (GamePad.GetState(PlayerIndex.One).Buttons.Y == ButtonState.Pressed)
            {
                MoveUp(moveDistance);
            }
            if (GamePad.GetState(PlayerIndex.One).Buttons.X == ButtonState.Pressed)
            {
                MoveLeft(moveDistance);
            }

            if (GamePad.GetState(PlayerIndex.One).ThumbSticks.Left.X > 0)
            {
                MoveRight((int)(moveDistance * GamePad.GetState(PlayerIndex.One).ThumbSticks.Left.X));
            }
            if (GamePad.GetState(PlayerIndex.One).ThumbSticks.Left.X < 0)
            {
                MoveLeft((int)(moveDistance * Math.Abs(GamePad.GetState(PlayerIndex.One).ThumbSticks.Left.X)));
            }



            base.Update(gameTime);
        }


        private void MoveOnKey(Keys key, int moveDistance)
        {
            switch (key)
            {
                case Keys.W:
                case Keys.Up:
                    MoveUp(moveDistance);
                    break;
                case Keys.A:
                case Keys.Left:
                    MoveLeft(moveDistance);
                    break;
                case Keys.S:
                case Keys.Down:
                    MoveDown(moveDistance);
                    break;
                case Keys.D:
                case Keys.Right:
                    MoveRight(moveDistance);
                    break;
            }
        }

        private void MoveUp(int moveDistance)
        {
            if (m_rectSessler.Y > 0)
            {
                m_rectSessler.Y = Math.Max(m_rectSessler.Y - moveDistance, 0);
            }
        }

        private void MoveDown(int moveDistance)
        {
            if (m_rectSessler.Bottom < this.graphics.GraphicsDevice.Viewport.Height)
            {
                m_rectSessler.Y = Math.Min(m_rectSessler.Y + moveDistance, this.graphics.GraphicsDevice.Viewport.Height);
            }
        }

        private void MoveLeft(int moveDistance)
        {
            if (m_rectSessler.Left > 0)
            {
                m_rectSessler.X = Math.Max(m_rectSessler.X - moveDistance, 0);
            }
        }

        private void MoveRight(int moveDistance)
        {
            if (m_rectSessler.Right < this.graphics.GraphicsDevice.Viewport.Width)
            {
                m_rectSessler.X = Math.Min(m_rectSessler.X + moveDistance, this.graphics.GraphicsDevice.Viewport.Width);
            }
        }








        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            //
            // Let's draw our sprite
            this.spriteBatch.Begin();

            this.spriteBatch.Draw(m_texSessler, m_rectSessler, Color.White);

            this.spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}





