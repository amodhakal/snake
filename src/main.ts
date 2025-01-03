// TODO: Add colors based on the different enum types for a piece

import { Asset, AssetManager, originalAsset } from "./AssetManager";
import { fragmentShaderString } from "./shaders/fragment";
import { vertexShaderString } from "./shaders/vertex";
import "./style.css";

const WIDTH = 35;
const HEIGHT = 16;

// Create canvas
const canvas = document.querySelector("canvas") as HTMLCanvasElement;
canvas.width = WIDTH * 50;
canvas.height = HEIGHT * 50;

// Create webgl context
const gl = canvas.getContext("webgl");
if (!gl) throw new Error("Couldn't create webgl context");

// Create an asset manager and add the assets to create a grid
new AssetManager(gl);

const ROW_INCREASE = 0.102;
const COL_INCREASE = 0.055;

for (let row = 0; row < HEIGHT * ROW_INCREASE; row += ROW_INCREASE) {
  for (let col = 0; col < WIDTH * COL_INCREASE; col += COL_INCREASE) {
    const newAsset: Asset = {
      vertices: originalAsset.vertices.map((vertice) => {
        return [vertice[0] + col, vertice[1] + row, vertice[2]];
      }),
      triangles: originalAsset.triangles,
      name: originalAsset.name,
    };
    AssetManager.addAsset(newAsset);
  }
}

// Get the buffers and sizes from the asset manager
const { verticeBuffer, triangleBuffer, size } = AssetManager.getBuffers();

// Compile fragment shaders
const fragmentShader = gl.createShader(gl.FRAGMENT_SHADER);
gl.shaderSource(fragmentShader, fragmentShaderString);
gl.compileShader(fragmentShader);
if (!gl.getShaderParameter(fragmentShader, gl.COMPILE_STATUS)) {
  throw new Error("Error fragment: " + gl.getShaderInfoLog(fragmentShader));
}

// Compile vertex shaders
const vertexShader = gl.createShader(gl.VERTEX_SHADER);
gl.shaderSource(vertexShader, vertexShaderString);
gl.compileShader(vertexShader);
if (!gl.getShaderParameter(vertexShader, gl.COMPILE_STATUS)) {
  throw new Error("Error vertex: " + gl.getShaderInfoLog(vertexShader));
}

// Createa and link shaders
const program = gl.createProgram();
gl.attachShader(program, fragmentShader);
gl.attachShader(program, vertexShader);
gl.linkProgram(program);
if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
  throw new Error("Error linking: " + gl.getProgramInfoLog(program));
}

// Activate shaders
gl.useProgram(program);

// Get attributes
const aPosition = gl.getAttribLocation(program, "aPosition");
gl.enableVertexAttribArray(aPosition);

// Render assets
gl.clearColor(6 / 255, 62 / 255, 45 / 255, 1);
gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

// Bind vertices
gl.bindBuffer(gl.ARRAY_BUFFER, verticeBuffer);
gl.vertexAttribPointer(aPosition, 3, gl.FLOAT, false, 0, 0);

// Bind triangles
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, triangleBuffer);
gl.drawElements(gl.TRIANGLES, size, gl.UNSIGNED_SHORT, 0);
