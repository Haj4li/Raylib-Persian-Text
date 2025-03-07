# Raylib C++ Game Development Template

![Raylib Logo](https://www.raylib.com/common/img/raylib_logo.png)

A ready-to-use Visual Studio Code template for C++ game development with Raylib. Quickly start 2D/3D games with preconfigured build tasks and project structure.

## 🚀 Features

- ⚡️ One-click build & debug configurations
- 📦 Preconfigured Raylib project setup
- 🛠️ CMake integration for cross-platform builds
- 📁 Organized project structure
- 🔄 Automatic asset path handling
- 🔧 Easy-to-customize build tasks

## ⏩ Quick Start

1. **Clone the repository**
   ```bash
   git clone https://github.com/Haj4li/Raylib-VScode-Cpp-Template.git
   cd raylib-cpp-template
   ```

2. **Open in VS Code**
   ```bash
   code .
   ```

3. **Build the project**
   - `Ctrl+Shift+P` → `Tasks: Run Task`
   - Choose `Build (Debug)` for development
   - Choose `Build (Release)` for final version

4. **Run the executable**
   ```bash
   ./main
   ```

## 📋 Prerequisites

- [VS Code](https://code.visualstudio.com/)
- [C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
- [Raylib](https://www.raylib.com/)

## 🛠 Building the Project

### Debug Build (Development)
```bash
# Via VS Code Task
Terminal > Run Task > Build (Debug)

### Release Build (Optimized)

# Via VS Code Task
Terminal > Run Task > Build (Release)
```
## 📂 Project Structure
```
.
├── src/              # Source files
│   └── gmae.cpp      # place your cpp files here
├── assets/           # Game assets directory
├── include/          # Header files
├── .vscode/          # VS Code configurations
│   ├── tasks.json    # Build tasks
│   └── settings.json # Workspace settings
└── CMakeLists.txt    # Build configuration
└── main.cpp          # Main game file
```

## 🔧 Configuration Options

Modify `.vscode/tasks.json` for:
- Custom build commands
- Additional build targets
- Pre/post-build hooks

## 🤝 Contributing
Pull requests welcome! For major changes, please open an issue first.

## 📄 License
[MIT](https://choosealicense.com/licenses/mit)

---

Made with ❤️ and [Raylib](https://www.raylib.com/)  
Maintained by Ali
