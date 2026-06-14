# Belief City - Psychological Survival Game

> An advanced **C++ OOP** survival game where your mind is the health bar. Move through a city of "Cognitive Assassins" and survive their psychological warfare with your sanity intact.

![C++](https://img.shields.io/badge/C%2B%2B17-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Paradigm](https://img.shields.io/badge/Paradigm-OOP-5B2C8A?style=flat-square)
![STL](https://img.shields.io/badge/STL-only-1572B6?style=flat-square)

## What is it?
Belief City is a console survival game built as a deep dive into **Object-Oriented Programming**. You play a **Seeker** navigating a city of psychological boss NPCs ("Cognitive Assassins") - each one attacks your **Global Sanity** and tests your **Rebellion Score** through branching decisions. Survive with your mind intact.

## OOP Architecture - 10 classes
| Principle | How it is used |
| :-- | :-- |
| **Abstraction** | `ConsciousEntity` abstract base with pure virtual functions |
| **Inheritance** | Multi-level: `ConsciousEntity -> CognitiveAssassin -> bosses` (The Gatekeeper, The Conversationalist, The Broken Giant, The Keeper of Red Lake, Insha) |
| **Polymorphism** | Runtime method overriding for NPC engagement |
| **Composition** | `BeliefCityEngine` owns all logic via **smart pointers** (`unique_ptr` - zero leaks) |
| **Analytics** | `PsychometricAnalyzer` tracks the player's evolving psyche |

## Build and Run
```bash
g++ -std=c++17 -O2 BeliefCity.cpp -o BeliefCity
./BeliefCity
```

## Tech
`C++17` - `STL` - `Smart Pointers` - `Polymorphism` - `Composition`

---
Built by **[Minhal Rizvi](https://github.com/minhalrizvi1224-dotcom)** - [LinkedIn](https://www.linkedin.com/in/minhal-rizvi-a14478354/)