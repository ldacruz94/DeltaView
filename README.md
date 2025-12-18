# DeltaView

A lightweight desktop application to compare text files and visualize differences side-by-side.

## Overview

DeltaView is a small C++/Qt application I made for quickly comparing two text inputs or files and highlighting the differences between them. It provides a simple, side-by-side interface where I can paste or load text and instantly see what changed, making it a quick and lightweight tool for checking edits or revisions.

## Features

- Side-by-side text comparison with clear highlighting
- Shows additions in green, deletions in red, and modifications in both colors
- Fast performance even with larger files
- Clean interface that's easy to use
- Can paste text directly or load from files

## Demo

![DeltaView Demo](misc/delta_view_demo.mp4)

## What I Used

- **C++ 20**
- **Qt 6** for the UI framework
- **Visual Studio 2022**
- **Windows 11**

## Why I Built This

I wanted a simple way to compare text without opening up heavyweight tools or dealing with version control systems. This lets me paste two chunks of text or load files and immediately see the differences highlighted, which is really useful when I'm reviewing config changes or checking what I edited in documentation.

I also started this little project to get more familiarized with Qt.

## Future Plans

Some things I'm thinking about adding:

- File import and export support
- Line numbers
- Better diff algorithms
- Maybe syntax highlighting for code
- Dark mode theme

## Project Notes

This is a personal project I built to learn more about Qt development and implement diff algorithms. The code isn't publicly available - this is just a portfolio piece showing what I built.

---

*The goal was to keep it simple and focused on usability rather than packing in every feature possible.*

*Side note: I tried using CMake for this, but for some reason my environment is simply refusing to allow CMake together with Qt so I'm stuck using MSBuild*