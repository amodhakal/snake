import { BG_COLOR, BOARD_DIMENSION, BOARD_VIEW_MULTIPLYER } from "./constants";
import "./style.css";

// Create WebGL context and add a green background
const canvas = document.querySelector("canvas") as HTMLCanvasElement;
canvas.width = BOARD_DIMENSION.width * BOARD_VIEW_MULTIPLYER;
canvas.height = BOARD_DIMENSION.height * BOARD_VIEW_MULTIPLYER;
const gl = canvas.getContext("webgl");
if (!gl) throw new Error("Couldn't create webgl context");
gl.clearColor(...BG_COLOR);
gl.clear(gl.COLOR_BUFFER_BIT);
