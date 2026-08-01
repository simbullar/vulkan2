#!/usr/bin/env sh

glslc shaders/source/shader.vert -o shaders/vert.spv
glslc shaders/source/shader.frag -o shaders/frag.spv
