import { BG_COLOR } from "./constants";

// Create WebGL context and add a green background
const canvas = document.querySelector("canvas") as HTMLCanvasElement;
const gl = canvas.getContext("webgl");
if (!gl) throw new Error("Couldn't create webgl context");
gl.clearColor(...BG_COLOR);
gl.clear(gl.COLOR_BUFFER_BIT);
