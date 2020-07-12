using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace ParticleLab.Particles
{
    public class ParticleEmitter
    {

        private Dictionary<int, Particle> m_Particles = new Dictionary<int, Particle>();
        private Texture2D m_texSmoke;
        private Texture2D m_texFire;
        private MyRandom m_Random = new MyRandom();

        private TimeSpan m_Rate;
        private int m_SourceX;
        private int m_SourceY;
        private int m_ParticleSize;
        private int m_Speed;
        private TimeSpan m_Lifetime;
        private TimeSpan m_Switchover;

        public Vector2 Gravity { get; set; }

        public ParticleEmitter(ContentManager Content, TimeSpan Rate, int SourceX, int SourceY, int Size, int Speed, TimeSpan Lifetime, TimeSpan Switchover)
        {
            m_Rate = Rate;
            m_SourceX = SourceX;
            m_SourceY = SourceY;
            m_ParticleSize = Size;
            m_Speed = Speed;
            m_Lifetime = Lifetime;
            m_Switchover = Switchover;

            m_texSmoke = Content.Load<Texture2D>("Smoke");
            m_texFire = Content.Load<Texture2D>("Fire");

            this.Gravity = new Vector2(0, 0);
        }

        private TimeSpan m_Accumulated = TimeSpan.Zero;

        /// <summary>
        /// Generates new particles, updates the state of existing ones and retires expired particles.
        /// </summary>
        public void Update(GameTime gameTime)
        {
            //
            // Generate particles at the specified rate
            m_Accumulated += gameTime.ElapsedGameTime;
            while (m_Accumulated > m_Rate)
            {
                m_Accumulated -= m_Rate;

                Particle p = new Particle(
                    m_Random.Next(),
                    new Vector2(m_SourceX, m_SourceY),
                    m_Random.NextCircleVector(),
                    (float)m_Random.NextGaussian(m_Speed, 1),
                    m_Lifetime);

                if (!m_Particles.ContainsKey(p.Name))
                {
                    m_Particles.Add(p.Name, p);
                }
            }


            //
            // For any existing particles, update them, if we find ones that have expired, add them
            // to the remove list.
            List<int> RemoveMe = new List<int>();
            foreach (Particle p in m_Particles.Values)
            {
                p.Lifetime -= gameTime.ElapsedGameTime;
                if (p.Lifetime < TimeSpan.Zero)
                {
                    //
                    // Add to the remove list
                    RemoveMe.Add(p.Name);
                }
                //
                // Update its position
                p.Position += (p.Direction * p.Speed);
                //
                // Have it rotate proportional to its speed
                p.Rotation += p.Speed / 50.0f;
                //
                // Apply some gravity
                p.Direction += this.Gravity;
            }

            //
            // Remove any expired particles
            foreach (int Key in RemoveMe)
            {
                m_Particles.Remove(Key);
            }
        }

        /// <summary>
        /// Renders the active particles
        /// </summary>
        public void Draw(SpriteBatch spriteBatch)
        {

            Rectangle r = new Rectangle(0, 0, m_ParticleSize, m_ParticleSize);
            foreach (Particle p in m_Particles.Values)
            {
                Texture2D texDraw;
                if (p.Lifetime < m_Switchover)
                {
                    texDraw = m_texSmoke;
                }
                else
                {
                    texDraw = m_texFire;
                }

                r.X = (int)p.Position.X;
                r.Y = (int)p.Position.Y;
                spriteBatch.Draw(
                    texDraw,
                    r,
                    null,
                    Color.White,
                    p.Rotation,
                    new Vector2(texDraw.Width / 2, texDraw.Height / 2),
                    SpriteEffects.None,
                    0);
            }
        }
    }
}
