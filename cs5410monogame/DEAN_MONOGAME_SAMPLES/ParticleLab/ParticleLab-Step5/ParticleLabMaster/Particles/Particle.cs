using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace ParticleLab.Particles
{
    public class Particle
    {
        public Particle(int Name, Vector2 Position, Vector2 Direction, float Speed, TimeSpan Lifetime,Texture2D Texture)
        {
            this.Name = Name;
            this.Position = Position;
            this.Direction = Direction;
            this.Speed = Speed;
            this.Lifetime = Lifetime;
            this.Texture = Texture;

            this.Rotation = 0;
        }

        public int Name;
        public Vector2 Position;
        public float Rotation;
        public Vector2 Direction;
        public float Speed;
        public TimeSpan Lifetime;
        public Texture2D Texture;
    }
}
