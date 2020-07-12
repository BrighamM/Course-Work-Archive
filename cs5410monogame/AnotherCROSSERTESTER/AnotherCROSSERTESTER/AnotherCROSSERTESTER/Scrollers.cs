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
    class ScrollingBackground
    {
        private Texture2D texture;
        private Texture2D secondTexture;
        private Rectangle rectangle;
        private Rectangle secondRectangle;

        public ScrollingBackground(Texture2D texture, Rectangle rectangle)
        {
            this.texture = texture;
            this.rectangle = rectangle;

            secondTexture = texture;
            secondRectangle = new Rectangle(0, -rectangle.Height, rectangle.Width, rectangle.Height);
        }

        public void update(bool fast = false, bool slow = false)
        {
            if (slow)
            {
                rectangle.Y += 1;
                secondRectangle.Y += 1;
            }
            else
            {
                rectangle.Y += 3;
                secondRectangle.Y += 3;
            }


            if (fast)
            {
                rectangle.Y += 3;
                secondRectangle.Y += 3;
            }

            if (rectangle.Y >= rectangle.Height)
            {
                rectangle.Y = -rectangle.Height;
            }
            if (secondRectangle.Y >= secondRectangle.Height)
            {
                secondRectangle.Y = -secondRectangle.Height;
            }
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(texture, rectangle, Color.LightCyan);
            spriteBatch.Draw(texture, secondRectangle, Color.LightCyan);
        }
    }
}
