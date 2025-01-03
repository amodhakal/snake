import { AssetManager, exampleAsset } from "./AssetManager";
import "./style.css";

// Create canvas
const canvas = document.querySelector("canvas") as HTMLCanvasElement;
canvas.width = 20 * 50;
canvas.height = 12 * 50;

// Create webgl context
const gl = canvas.getContext("webgl");
if (!gl) throw new Error("Couldn't create webgl context");
gl.clearColor(6 / 255, 62 / 255, 45 / 255, 1);
gl.clear(gl.COLOR_BUFFER_BIT);

// Create an asset manager and add an asset
new AssetManager(gl)
AssetManager.addAsset(exampleAsset)

// Get the buffers and sizes from the asset manager
// const { verticeBuffer, triangleBuffer, size } = AssetManager.getBuffers()
