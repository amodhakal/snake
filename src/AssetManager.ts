type Vec3 = [number, number, number];

export interface Asset {
  vertices: Vec3[];
  triangles: Vec3[];
}

export interface Buffers {
  verticeBuffer: WebGLBuffer;
  triangleBuffer: WebGLBuffer;
  size: number;
}

export const exampleAsset: Asset = {
  vertices: [
    [-0.35, 0.1, 0],
    [-0.25, 0.4, 0],
    [-0.15, 0.1, 0],
  ],
  triangles: [[0, 1, 2]],
};

export class AssetManager {
  static assets: Asset[] = [];
  static gl: WebGLRenderingContext;

  constructor(gl: WebGLRenderingContext) {
    AssetManager.gl = gl;
  }

  static addAsset(asset: Asset) {
    AssetManager.assets.push(asset);
  }

  static getBuffers(): Buffers {
    const { assets, gl } = AssetManager;
    if (assets.length <= 0) {
      throw new Error("Missing assets to load");
    }

    let vertices: number[] = [];
    let points = [];
    let pointOffset = 0;

    for (const asset of assets) {
      for (const vertice of asset.vertices) {
        vertices.push(...vertice);
      }

      for (const triangle of asset.triangles) {
        for (const point of triangle) {
          points.push(point + pointOffset);
        }
      }

      pointOffset += asset.vertices.length;
    }

    const verticeBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, verticeBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

    const triangleBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, triangleBuffer);
    gl.bufferData(
      gl.ELEMENT_ARRAY_BUFFER,
      new Uint16Array(points),
      gl.STATIC_DRAW
    );

    return { verticeBuffer, triangleBuffer, size: points.length };
  }
}
