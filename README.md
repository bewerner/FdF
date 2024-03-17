# FdF

![Title_Image](images/title.png)

The goal of this project was to represent any given heightmap as a wireframe model in isometric view using the [MLX42](https://github.com/codam-coding-college/MLX42) library.

---

<div style="text-align: center; display: flex; flex-wrap: wrap;">
<div style="min-width:max-content; margin-right: 25px;">

Heightmap text file:
```
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 1 1 0 0 1 1 0 0 0 1 1 1 1 1 0 0 0
0 0 1 1 0 0 1 1 0 0 0 0 0 0 0 1 1 0 0
0 0 1 1 0 0 1 1 0 0 0 0 0 0 0 1 1 0 0
0 0 1 1 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0
0 0 0 1 1 1 1 1 0 0 0 1 1 0 0 0 0 0 0
0 0 0 0 0 0 1 1 0 0 0 1 1 0 0 0 0 0 0
0 0 0 0 0 0 1 1 0 0 0 1 1 1 1 1 1 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```
</div>
<div>
<div style="text-align: center;">Graphical representation:<br><br></div>

![Alt text](images/mandatory.png)

</div>
</div>

---

# Dependencies


#### Debian / Ubuntu
```
sudo apt update
sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev
```

#### Arch (x11)
```
sudo pacman -S glfw-x11
```

#### Arch (wayland)
```
sudo pacman -S glfw-wayland
```

#### MacOS
```
brew install glfw
brew install cmake
```

---

# Installation

```
git clone https://github.com/bewerner/FdF.git
cd FdF
make
```

---

# Usage

`./fdf path_to_heightmap.fdf`\
`./fdf path_to_heightmap.png`\
`./fdf path_to_heightmap.png path_to_colormap.png`

### Or use these presets to load the included maps:

`make ft`

`make alien`\
`make foggy`\
`make crater`

`make mud`\
`make pebbles`\
`make cobblestone`

---

# Bonus Features

- Free mesh rotation and zoom
- Perspective projection and adjustable Field of View
- Antialiased lines
- Adjustable line thickness (no Antialiasing)
- Skybox environment
- Color gradient from lowest to highest point
- Ability to load PNG heightmaps
- Ability to load PNG colormaps
- FPS display (frames per second)
- Additional draw modes:
	- Vertices only (adjustable vertex size)
	- Dotted edges (adjustable dot size)
	- Edges
	- Faces
	- Faces and edges

---

# Controls

### Universal Controls:

| Key⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	| Description⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	|
|-------------------------------------------|---------------------------------------------------|
| <kbd>Scroll Wheel</kbd>					| Zoom												|
| <kbd>Left Mouse Button</kbd>				| Move mesh											|
| <kbd>Right  Mouse Button</kbd>			| Rotate mesh										|
| <kbd>Middle Mouse Button</kbd>			| Change height scale								|
| <kbd>Shift</kbd> + <kbd>Scroll Wheel</kbd>| Change Field of View								|
| <kbd>R</kbd> or <kbd>Double Click</kbd>	| Reset map position								|
| <kbd>P</kbd>								| Perspective projection							|
| <kbd>O</kbd>								| Orthographic projection							|
| <kbd>I</kbd>								| Isometric projection								|
| <kbd>Shift</kbd> + <kbd>↑</kbd>			| Increase height scale								|
| <kbd>Shift</kbd> + <kbd>↓</kbd>			| Decrease height scale								|
| <kbd>S</kbd>								| Change skybox										|
| <kbd>Shift</kbd> + <kbd>S</kbd>			| Toggle skybox										|
| <kbd>F</kbd>								| Toggle FPS (Frames per second)					|

### Draw Modes:

| Key⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	| Description⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	|
|-------------------------------------------|---------------------------------------------------|
| <kbd>1</kbd>								| Draw vertices										|
| <kbd>2</kbd>								| Draw dotted edges									|
| <kbd>3</kbd>								| Draw edges										|
| <kbd>4</kbd>								| Draw faces										|
| <kbd>5</kbd>								| Draw faces and edges								|

### Edge Mode Controls: ( <kbd>4</kbd> )

| Key⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	| Description⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	|
|-------------------------------------------|---------------------------------------------------|
| <kbd>A</kbd>								| Toggle antialiasing								|
| <kbd>↑</kbd>								| Increase line thickness (only with AA disabled)	|
| <kbd>↓</kbd>								| Decrease line thickness (only with AA disabled)	|

### Vertex Mode Controls: ( <kbd>1</kbd> )

| Key⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	| Description⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	|
|-------------------------------------------|---------------------------------------------------|
| <kbd>↑</kbd>								| Increase vertex size	$\color{red}*$				|
| <kbd>↓</kbd>								| Decrease vertex size	$\color{red}*$				|

### Dotted Edge Mode Controls: ( <kbd>2</kbd> )

| Key⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	| Description⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	|
|----------------------------------------|-------------------------------------------------|
| <kbd>↑</kbd>							 | Increase dot size		$\color{red}*$			|
| <kbd>↓</kbd>							 | Decrease dot size		$\color{red}*$			|
| <kbd>→</kbd>							 | Increase dot density		$\color{red}*$			|
| <kbd>←</kbd>							 | Decrease dot density		$\color{red}*$			|


$\color{red}*$ *Only use on small maps! Might freeze the program.*
