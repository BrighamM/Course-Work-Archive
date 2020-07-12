using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace ParticleLab
{
	/// <summary>
	/// Implements an Instanced Model type, taking the built-in XNA Model type
	/// as a constructor parameter and working from it.
	/// </summary>
	public class MyInstancedModel
	{
		public MyInstancedModel(GraphicsDevice graphicsDevice, Model BaseModel)
		{
			//
			// Save the original model for nostalgia's sake
			m_BaseModel = BaseModel;
			//
			// Take this model, write a new vertex declaration and construct
			// new index and vertex buffers to support the instancing.
			BuildInstancedData(graphicsDevice, BaseModel);
		}

		private const int MAX_SHADER_INSTANCES = 25;
		private Model m_BaseModel;

		public List<MyInstancedModelMesh> Meshes
		{
			get { return m_Meshes; }
		}
		private List<MyInstancedModelMesh> m_Meshes=new List<MyInstancedModelMesh>();

		/// <summary>
		/// Transforms the original Model meshes into instanced meshes
		/// </summary>
		/// <param name="BaseModel"></param>
		private void BuildInstancedData(GraphicsDevice graphicsDevice, Model BaseModel)
		{
			//
			// Transform the original model meshes into instanced meshes
			foreach (ModelMesh Mesh in BaseModel.Meshes)
			{
				MyInstancedModelMesh InstancedMesh = new MyInstancedModelMesh(graphicsDevice, Mesh,MAX_SHADER_INSTANCES);
				this.Meshes.Add(InstancedMesh);
			}
		}

		public void Draw(GraphicsDevice graphicsDevice, Effect effect, Matrix[] InstanceTransforms, Matrix[] InstanceRotations, Matrix mView, Matrix mProjection, Texture2D Texture)
		{
			//
			// Set the render states
			effect.Parameters["View"].SetValue(mView);
			effect.Parameters["Projection"].SetValue(mProjection);
			effect.Parameters["Texture"].SetValue(Texture);

			foreach (MyInstancedModelMesh Mesh in m_Meshes)
			{
				Mesh.Draw(graphicsDevice, effect, InstanceTransforms, InstanceRotations, MAX_SHADER_INSTANCES);
			}
		}
	}
}
