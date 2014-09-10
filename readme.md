# About Fritzing #

**[Fritzing](http://fritzing.org)** is an open-source initiative to support designers and artists to take the step from physical prototyping to actual product. We are creating this software in the spirit of Processing and Arduino, that allows the designer / artist / researcher / hobbyist to document their Arduino-based prototype and create a PCB layout for manufacturing. The complimenting website helps to share and discuss drafts and experiences as well as to reduce manufacturing costs.

**[Fritzing](http://fritzing.org/download/)** is essentially an Electronic Design Automation software with a low entry barrier, suited for the needs of designers and artists. It uses the metaphor of the breadboard, so that it is easy to transfer your hardware sketch to the software. From there it is possible to create PCB layouts for turning it into a robust PCB yourself or by help of a manufacturer.

More information may be found on the project website at [http://fritzing.org](http://fritzing.org)

Downloads are available at [http://fritzing.org/download](http://fritzing.org/download)

# Folderstructure #

## Fritzing##
	
### bins ###
fritzing-part-bin files (fzb) integrated in the Parts-palette

### help ###
helping file for the parts-editor

### part-gen-scripts ###
helping (python-) scripts for faster part-creation and e.g. svg-cleanup

### parts ###
<<<<<<< HEAD
the fritzing parts folders. all the svg-files for the core parts and remotebranch for easily updating fritzing parts
=======
the fritzing parts folders. all the svg-files for the fritzing-parts. it is based on a remotebranch and can be easily updated. the parts repository:
[https://github.com/el-j/fritzing-parts](http://github.com/el-j/fritzing-parts)
>>>>>>> 17d8097289c6cb63c03e9ef350423b1a87957912

### pdb ###
the fritzing data-base referenz for all the core-parts included in parts.db

### pri ###

### recources ###
recources for the fritzing application. including main-bins, fonts, images, parts, obsolete, styles, templates etc.

### sketches ###
including the example-sketches which gets shipped with the application.

### src ###
the programmcode for the fritzing-application

### tools ###
tools for fritzing. including brd2svg, stable-release-maker and other tools

### translations ###
<<<<<<< HEAD
the languagefiles for fritzing.
=======
the languagefiles for fritzing.
>>>>>>> 17d8097289c6cb63c03e9ef350423b1a87957912
