using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace ParticleLabMaster
{
    class Particle
    {
        public Particle(int Name, Vector2 Position, Vector2 Direction, float Speed, TimeSpan Lifetime)
        {
            this.Name = Name;
            this.Position = Position;
            this.Direction = Direction;
            this.Speed = Speed;
            this.Lifetime = Lifetime;

            this.Rotation = 0;
            this.Alive = TimeSpan.Zero;
        }

        public int Name;
        public Vector2 Position;
        public float Rotation;
        public Vector2 Direction;
        public float Speed;
        public TimeSpan Alive;
        public TimeSpan Lifetime;
        public Texture2D Texture;
    }
}
