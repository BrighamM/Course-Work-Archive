using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace ParticleLab
{
	public class MyInstancedModelMesh
	{
		/// <summary>
		/// Converts a ModelMesh into our instanced mesh.  This class makes the MOTHER of assumptions
		/// that only one mesh part is in the model.  If the model has more than one part, this class
		/// needs to be extended to have a container of MyInstancedModelMeshParts.  It wouldn't be hard
		/// to do, but I have other things to get to right now, perhaps later I'll come back and add it.
		/// </summary>
		public MyInstancedModelMesh(GraphicsDevice graphicsDevice, ModelMesh BaseMesh,int MaxShaderInstances)
		{
			//
			// Define a new vertex declaration, to add the index for the Instance Matrices
			ExtendVertexDeclaration(graphicsDevice, BaseMesh);

			ReplicateVertexData(graphicsDevice, BaseMesh,MaxShaderInstances);
			ReplicateIndexData(graphicsDevice, BaseMesh, MaxShaderInstances);

			m_TempTransforms = new Matrix[MaxShaderInstances];
			m_TempRotations = new Matrix[MaxShaderInstances];
		}

		private VertexBuffer m_VertexBuffer;
		private IndexBuffer m_IndexBuffer;
		private VertexDeclaration m_VertexDeclaration;
		private short m_VertexStride;
		private int m_VertexCount;
		private int m_IndexCount;

		//
		// Array of temporary matrices for the ShaderInstancing technique
		Matrix[] m_TempTransforms;
		Matrix[] m_TempRotations;

		/// <summary>
		/// Create the new vertex declaration, which includes the index to the Instance
		/// Specific transformation matrices.
		/// </summary>
		/// <param name="BaseMesh"></param>
		private void ExtendVertexDeclaration(GraphicsDevice graphicsDevice, ModelMesh BaseMesh)
		{
			m_VertexStride = (short)BaseMesh.MeshParts[0].VertexStride;

			//
			// We'll use the Texcoord1 to as a white lie for the instance index
			VertexElement[] NewElement =
            {
                new VertexElement((short)0, (short)m_VertexStride,
                                  VertexElementFormat.Single,
                                  VertexElementMethod.Default,
                                  VertexElementUsage.TextureCoordinate, 1)
            };

			//
			// Add the new element to whatever was already there
			int TotalLength = BaseMesh.MeshParts[0].VertexDeclaration.GetVertexElements().Length + NewElement.Length;
			VertexElement[] elements = new VertexElement[TotalLength];
			
			BaseMesh.MeshParts[0].VertexDeclaration.GetVertexElements().CopyTo(elements,0);
			NewElement.CopyTo(elements, BaseMesh.MeshParts[0].VertexDeclaration.GetVertexElements().Length);

			//
			// Create the new vertex declaration.
			m_VertexDeclaration = new VertexDeclaration(graphicsDevice, elements);
			VertexElement[] e = m_VertexDeclaration.GetVertexElements();
		}

		/// <summary>
		/// For each supported instance of the model on the shader, we require a copy of the
		/// vertex buffer data along with adding the shader instance matrix index.
		/// </summary>
		void ReplicateVertexData(GraphicsDevice graphicsDevice, ModelMesh BaseMesh, int MaxShaderInstances)
		{
			m_VertexCount = BaseMesh.MeshParts[0].NumVertices;
			//
			// Read the existing vertex buffer data
			byte[] oldVertexData = new byte[m_VertexCount * m_VertexStride];
			BaseMesh.VertexBuffer.GetData(oldVertexData);

			//
			// Adjust the vertex stride to include our additional index channel.
			int oldVertexStride = BaseMesh.MeshParts[0].VertexStride;

			m_VertexStride += sizeof(float);

			//
			// Allocate a temporary array to hold the replicated vertex data.
			byte[] NewVertexData = new byte[m_VertexCount * m_VertexStride * MaxShaderInstances];

			int outputPosition = 0;

			// Replicate one copy of the original vertex buffer for each instance.
			for (int Instance = 0; Instance < MaxShaderInstances; Instance++)
			{
				int sourcePosition = 0;

				// Convert the instance index from float into an array of raw bits.
				byte[] instanceIndexBits = BitConverter.GetBytes((float)Instance);

				for (int i = 0; i < m_VertexCount; i++)
				{
					// Copy over the existing data for this vertex.
					Array.Copy(oldVertexData, sourcePosition,
							   NewVertexData, outputPosition, oldVertexStride);

					outputPosition += oldVertexStride;
					sourcePosition += oldVertexStride;

					// Set the value of our new index channel.
					instanceIndexBits.CopyTo(NewVertexData, outputPosition);

					outputPosition += instanceIndexBits.Length;
				}
			}

			// Create a new vertex buffer, and set the replicated data into it.
			m_VertexBuffer = new VertexBuffer(
				graphicsDevice, 
				NewVertexData.Length, 
				BufferUsage.None);

			m_VertexBuffer.SetData(NewVertexData);
		}

		/// <summary>
		/// For each supported instance of the model on the shader, we require a copy of the
		/// index buffer data.
		/// </summary>
		void ReplicateIndexData(GraphicsDevice graphicsDevice, ModelMesh BaseMesh, int MaxShaderInstances)
		{
			// Read the existing index data, then destroy the existing index buffer.
			m_IndexCount=0;
			switch (BaseMesh.IndexBuffer.IndexElementSize)
			{
				case IndexElementSize.SixteenBits:
					m_IndexCount = BaseMesh.IndexBuffer.SizeInBytes / 2;
					break;
				case IndexElementSize.ThirtyTwoBits:
					m_IndexCount = BaseMesh.IndexBuffer.SizeInBytes / 4;
					break;
			}
			ushort[] oldIndices = new ushort[m_IndexCount];
			BaseMesh.IndexBuffer.GetData(oldIndices);

			//
			// Allocate a temporary array to hold the replicated index data.
			ushort[] newIndices = new ushort[m_IndexCount * MaxShaderInstances];

			int outputPosition = 0;

			// Replicate one copy of the original index buffer for each instance.
			for (int instanceIndex = 0; instanceIndex < MaxShaderInstances; instanceIndex++)
			{
				int instanceOffset = instanceIndex * m_VertexCount;

				for (int i = 0; i < m_IndexCount; i++)
				{
					newIndices[outputPosition] = (ushort)(oldIndices[i] + instanceOffset);

					outputPosition++;
				}
			}

			// Create a new index buffer, and set the replicated data into it.
			m_IndexBuffer = new IndexBuffer(
				graphicsDevice,
				sizeof(ushort) * newIndices.Length,
				BufferUsage.None,
				IndexElementSize.SixteenBits);

			m_IndexBuffer.SetData(newIndices);
		}

		public void Draw(GraphicsDevice graphicsDevice, Effect effect, Matrix[] InstanceTransforms, Matrix[] InstanceRotations, int MaxShaderInstances)
		{

			graphicsDevice.VertexDeclaration = m_VertexDeclaration;
			graphicsDevice.Vertices[0].SetSource(m_VertexBuffer, 0, m_VertexStride);
			graphicsDevice.Indices = m_IndexBuffer;
			effect.CurrentTechnique = effect.Techniques[0];

			effect.Begin();

			foreach (EffectPass pass in effect.CurrentTechnique.Passes)
			{
				pass.Begin();

				// We can only fit maxInstances into a single call. If asked to draw
				// more than that, we must split them up into several smaller batches.
				for (int Instance = 0; Instance < InstanceTransforms.Length; Instance += MaxShaderInstances)
				{
					// How many instances can we fit into this batch?
					int CurrentCount = InstanceTransforms.Length - Instance;

					if (CurrentCount > MaxShaderInstances)
						CurrentCount = MaxShaderInstances;

					// Upload transform matrices as shader constants.
					Array.Copy(InstanceTransforms, Instance, m_TempTransforms, 0, CurrentCount);
					Array.Copy(InstanceRotations, Instance, m_TempRotations, 0, CurrentCount);

					effect.Parameters["InstanceTransforms"].SetValue(m_TempTransforms);
					effect.Parameters["InstanceRotations"].SetValue(m_TempRotations);
					effect.CommitChanges();

					// Draw maxInstances copies of our geometry in a single batch.
					graphicsDevice.DrawIndexedPrimitives(
						PrimitiveType.TriangleList,
						0, 0, CurrentCount * m_VertexCount,
						0, CurrentCount * m_IndexCount / 3);
				}

				pass.End();
			}

			effect.End();
		}
	}
}
