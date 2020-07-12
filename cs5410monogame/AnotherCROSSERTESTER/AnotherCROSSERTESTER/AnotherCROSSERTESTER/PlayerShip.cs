using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;


namespace AnotherCROSSERTESTER
{
    class PlayerShip
    {

        public PlayerShip(int xPos, int yPos)
        {
            this.shipPosition.X = xPos;
            this.shipPosition.Y = yPos;
        }

        public Texture2D shipTexture;

        public Point shipPosition;

        public double rotation = 3.0;




        public void moveShipLeft()
        {
            this.shipPosition.X -= 10;
        }
        public void moveShipRight()
        {
            this.shipPosition.X += 10;
        }
        public void moveShipUp()
        {
            this.shipPosition.Y -= 10;
        }
        public void moveShipDown()
        {
            this.shipPosition.Y += 10;
        }



        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(getShipTexture(), new Rectangle(shipPosition.X, shipPosition.Y, getShipTexture().Width / 4, getShipTexture().Height / 4), Color.White);
        }



        public Texture2D getShipTexture()
        {
            return shipTexture;
        }
        public void setShipTexture(Texture2D input2DTexture)
        {
            shipTexture = input2DTexture;
        }
    }
}
