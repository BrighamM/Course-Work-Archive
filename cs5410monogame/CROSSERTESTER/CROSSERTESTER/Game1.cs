using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace CROSSERTESTER
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class Game1 : Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        
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
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();

            // TODO: Add your update logic here

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.DarkGray);

            // TODO: Add your drawing code here

            base.Draw(gameTime);
        }
    }
}


/*
 * Windows
 * 
 *Here is how we load assets
 * 
 * 1. Right click on Content.mgcb and select open with find the monogame pipeline tool and set as default and then click OK
 * 
 * 2. Double Click on content.mgcb
 * 2a. Select the monogameContent Symbol and make sure it matches whatever platform we are on.
 * 2b. Right Click on the monogameConten Symbol and select add existing item
 * 2c. Navigate to the files, select them and choose open.
 * 2d. Click save and then build.
 * 2e. Close the pipeline tool.
 * 
 * 3. Now right click on the Content folder and select add existing item. (LINUX = Add Files)
 * 3a. Content -> bin -> <OS> -> Show all file types -> select desired file types
 * 
 * 
 * 
 */


/*
 * 
 * 
 * Content for Mac
 * 
 * 1. Run Monogame pipeline tool.
 * 2. Using the pipeline tool open content.mgcb in the Content folder of your project.
 * 3. Click on the icon to verify the appropriate OS
 * 4. Select "Add Existing Item"
 * 5. Navigate to the item desired
 * 6. Copy the file to the directory
 * 7. Build
 * 8. Save 
 * 9. Close the pipeline tool
 * 10. Now Under the Content folder in your project select "Add Existing Files"
 * 11. Content -> bin -> OS -> Show all file types.
 * 12. Select the file. It should be called something like <fileName>.xnb
 * 13. Copy the file.
 * 
 * 
 * 
 * 
 */
