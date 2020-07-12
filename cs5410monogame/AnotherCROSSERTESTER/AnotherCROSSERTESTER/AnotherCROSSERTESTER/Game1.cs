using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Audio;

namespace AnotherCROSSERTESTER
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class Game1 : Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        PlayerShip playerShip;

        ScrollingBackground scrolling1;
        ScrollingBackground scrolling2;
        ScrollingBackground scrolling3;

        List<Texture2D> circleTextureList;
        List<PlayerShipProjectile> projectileList;

        Texture2D someCircle;

        SoundEffect tempSound;
        SoundEffect anotherSound;

        MouseState previousMouseState;

        SpriteFont spriteFont;

        int score = 0;

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            graphics.PreferredBackBufferHeight = 700; // USE 700 AND 1000 TREAT LIKE CONSTANTS
            graphics.PreferredBackBufferWidth = 1000;
            Content.RootDirectory = "Content";
            this.IsMouseVisible = true;
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            playerShip = new PlayerShip(300, 300);
            circleTextureList = getCircleTextureList();
            projectileList = new List<PlayerShipProjectile>();

            previousMouseState = Mouse.GetState();

            base.Initialize();
        }


        private List<Texture2D> getCircleTextureList()
        {
            List<Texture2D> returnList = new List<Texture2D>();

            for (int i = 5; i < 500; i++)
            {
                returnList.Add(createCircleText(i));
            }
            return returnList;
        }

        Texture2D createCircleText(int radius)
        {
            Texture2D texture = new Texture2D(GraphicsDevice, radius, radius);
            Color[] colorData = new Color[radius * radius];

            float diam = radius / 2f;
            float diamsq = diam * diam;

            for (int x = 0; x < radius; x++)
            {
                for (int y = 0; y < radius; y++)
                {
                    int index = x * radius + y;
                    Vector2 pos = new Vector2(x - diam, y - diam);
                    if (pos.LengthSquared() <= diamsq)
                    {
                        colorData[index] = Color.White;
                    }
                    else
                    {
                        colorData[index] = Color.Transparent;
                    }
                }
            }

            texture.SetData(colorData);
            return texture;
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);

            scrolling1 = new ScrollingBackground(Content.Load<Texture2D>("spr_stars02"), new Rectangle(0, 0, graphics.PreferredBackBufferWidth, graphics.PreferredBackBufferHeight));
            scrolling2 = new ScrollingBackground(Content.Load<Texture2D>("spr_stars01"), new Rectangle(0, 0, graphics.PreferredBackBufferWidth, graphics.PreferredBackBufferHeight));
            scrolling3 = new ScrollingBackground(Content.Load<Texture2D>("seamless space"), new Rectangle(0, 0, graphics.PreferredBackBufferWidth, graphics.PreferredBackBufferHeight));
            playerShip.setShipTexture(Content.Load<Texture2D>("Titan"));
            tempSound = Content.Load<SoundEffect>("slimeball");
            anotherSound = Content.Load<SoundEffect>("BossMain");
            anotherSound.CreateInstance().Play();

            spriteFont = Content.Load<SpriteFont>("hackfont2");

            someCircle = createCircleText(25);
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

            MouseState currentMouseState = Mouse.GetState();

            if (currentMouseState.LeftButton == ButtonState.Pressed && (previousMouseState.LeftButton != ButtonState.Pressed))
            {
                projectileList.Add(new PlayerShipProjectile(currentMouseState.Position, circleTextureList[77]));
                tempSound.CreateInstance().Play();
                score += 17;
            }


            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
            {
                Exit();
            }


            if (Keyboard.GetState().IsKeyDown(Keys.W) && playerShip.shipPosition.Y > 10)
            {
                playerShip.moveShipUp();
            }
            if (Keyboard.GetState().IsKeyDown(Keys.A) && playerShip.shipPosition.X > 10)
            {
                playerShip.moveShipLeft();
            }
            if (Keyboard.GetState().IsKeyDown(Keys.S) && playerShip.shipPosition.Y < graphics.PreferredBackBufferHeight - 90)
            {
                playerShip.moveShipDown();
            }
            if (Keyboard.GetState().IsKeyDown(Keys.D) && playerShip.shipPosition.X < graphics.PreferredBackBufferWidth - 80)
            {
                playerShip.moveShipRight();
            }


            foreach (var projectile in projectileList)
            {
                projectile.update();
            }

            if (Keyboard.GetState().IsKeyDown(Keys.Space))
            {
                projectileList.Add(new PlayerShipProjectile(playerShip.shipPosition, circleTextureList[17]));
                tempSound.CreateInstance().Play();
                score++;
            }





            scrolling1.update();
            scrolling2.update(true);
            scrolling3.update(false, true);

            previousMouseState = currentMouseState;


            base.Update(gameTime);
        }


        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);

            double framerate = (1.0 / (double)gameTime.ElapsedGameTime.TotalSeconds);
            this.Window.Title = "GAME STRESS TEST: " + framerate.ToString();


            spriteBatch.Begin();
            scrolling3.Draw(spriteBatch);
            scrolling1.Draw(spriteBatch);
            scrolling2.Draw(spriteBatch);

            foreach (var projectile in projectileList)
            {
                projectile.Draw(spriteBatch);
            }

            spriteBatch.DrawString(spriteFont, "SUPER SCORE!!! : " + score.ToString(), new Vector2(100, 100), Color.Red);

            playerShip.Draw(spriteBatch);
            spriteBatch.End();

            // TODO: Add your drawing code here

            base.Draw(gameTime);
        }
    }
}
