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
		public MyInstancedModel(GraphicsDevice graphicsDevice, Model BaseModel, int ExpectedMax)
		{
			//
			// Take this model, write a new vertex declaration and construct
			// new index and vertex buffers to support the instancing.
			BuildInstancedData(graphicsDevice, BaseModel);

			m_InstanceTransforms = new Matrix[ExpectedMax];
			m_InstanceRotations = new Matrix[ExpectedMax];
		}

		private const int MAX_SHADER_INSTANCES = 25;
		private Matrix[] m_InstanceTransforms;
		private Matrix[] m_InstanceRotations;
		private int m_InstanceCount = 0;

		/// <summary>
		/// Container for all the meshes in the model
		/// </summary>
		private List<MyInstancedModelMesh> Meshes
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

		/// <summary>
		/// Public method that allows client code to build up a bunch of instances to draw.  This all 
		/// does NOT draw them, it only accumulates the instance transforms.
		/// </summary>
		//public void Draw(GraphicsDevice graphicsDevice, Effect effect, Matrix[] InstanceTransforms, Matrix[] InstanceRotations, Matrix mView, Matrix mProjection, Texture2D Texture)
		public bool Draw(Matrix mTransform, Matrix mRotation)
		{
			//
			// Ensure we have room for the new instance
			if (m_InstanceCount >= m_InstanceRotations.Length) return false;

			m_InstanceRotations[m_InstanceCount] = mRotation;
			m_InstanceTransforms[m_InstanceCount] = mTransform;

			m_InstanceCount++;

			return true;
		}

		/// <summary>
		/// Commits all the accumulated draw calls...this performs the shader instancing
		/// </summary>
		public void Flush(GraphicsDevice graphicsDevice, Effect effect, Matrix mView, Matrix mProjection)
		{
			//
			// Apply the view/projection matrices
			effect.Parameters["View"].SetValue(mView);
			effect.Parameters["Projection"].SetValue(mProjection);

			foreach (MyInstancedModelMesh Mesh in m_Meshes)
			{
				Mesh.Draw(graphicsDevice, effect, m_InstanceTransforms, m_InstanceRotations, MAX_SHADER_INSTANCES);
			}

			m_InstanceCount = 0;
		}
	}
}
