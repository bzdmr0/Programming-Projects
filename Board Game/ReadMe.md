# Board Game (Gold Rush Alaska)

## Assignment Context

This is the last assignment of the Programming Language Concepts course.

Collaborator: **Arda Menşur**

The original assignment description is provided in the project PDF.

## Project Overview

The project implements a simplified two-player board game called **Gold Rush Alaska**.

- The board is an `n x n` square valley (`n >= 5`).
- Players take turns selecting coordinates.
- Cells contain hidden resources or wild animals.
- The objective is to collect as much gold as possible (score-based winner).

## Game Requirements Summary

- The board is populated randomly with Food, Wood, Medical Supplies, Gold, Wolves, and Bears.
- Wolves are twice the number of bears.
- Players track both **health** and **score**.
- Gold increases score (`+100` points).
- Food, Wood, and Medical Supplies increase health.
- Wild animals trigger an even/odd guess mechanic; wrong guesses cause damage.
- If a player's health reaches `0`, that player dies and the other may continue.

## Resource Effects (as given in the assignment)

- **Food**: increase health by `⌊n/6⌋`
- **Wood**: increase health by `⌊n/8⌋`
- **Medical Supplies**: increase health by `⌊n/4⌋`
- **Wolf**: even/odd dice effect, damage `⌊n/4⌋`
- **Bear**: even/odd dice effect, damage `⌊n/2⌋`
- **Gold**: increase score by `100`

Notes from the assignment:
- Some elements occupy multiple adjacent cells (for example, Wood and Bear).
- Each element effect can be activated only once per cell.
