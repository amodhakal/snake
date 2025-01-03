import "./style.css";

const canvas = document.querySelector("canvas") as HTMLCanvasElement;
canvas.width = 20 * 50;
canvas.height = 12 * 50;

const gl = canvas.getContext("webgl");
if (!gl) throw new Error("Couldn't create webgl context");
gl.clearColor(6 / 255, 62 / 255, 45 / 255, 1);
gl.clear(gl.COLOR_BUFFER_BIT);
