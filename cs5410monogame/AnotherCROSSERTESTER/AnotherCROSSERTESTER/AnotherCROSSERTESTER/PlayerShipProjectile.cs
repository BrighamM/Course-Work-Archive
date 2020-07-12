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
    class PlayerShipProjectile
    {

        public PlayerShipProjectile(Point shipPosition, Texture2D inputTexture)
        {
            projTexture = inputTexture;
            projectileRectangle = new Rectangle(shipPosition.X, shipPosition.Y, inputTexture.Width, inputTexture.Height);

        }

        Texture2D projTexture;
        Rectangle projectileRectangle;

        public void update()
        {
            projectileRectangle.Y -= 19;
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            Random random = new Random();
            int r = random.Next() % 255;
            int g = random.Next() % 255;
            int b = random.Next() % 255;
            Color color = new Color(r, g, b);
            spriteBatch.Draw(projTexture, projectileRectangle, color);
        }
    }
}
