# TaskbarToggle

A simple application that completely hides the Windows taskbar.

The Windows taskbar can be hidden in the system settings, after which it may be made visible again by hovering over it with the mouse cursor. This often creates an inconvenience when trying to click on something at the bottom of the screen, so when it's done, you may run this application, and it will hide the taskbar entirely, so it will not respond to the mouse cursor. While the application is running, you can repeatedly press the selected keyboard shortcut and it will hide or show the taskbar on your demand.

The application can be launched by a keyboard shortcut. For that, in Windows, just place a shortcut to this application in the folder at `C:\Users\%username%\AppData\Roaming\Microsoft\Windows\Start Menu`, right-click on it to open **Properties**, and set a convenient combination in the **Shortcut key** field. You can choose the same keyboard shortcut as the one set in the application, since it will not be launched more than once.

Since the application does not have a visible window, it is also exited using a keyboard shortcut. If there is a problem and you are unable to exit, you can always open the task manager by pressing `Ctrl+Shift+Esc` or `Ctrl+Alt+Delete` and find the application in the background processes list by it's name `taskbar-toggle.exe`. Then you can just right-click on it and shoose **End task** option.

## Settings

The application folder contains the `settings.ini` configuration file. The `[shortcuts]` section allows you to set arbitrary keyboard shortcuts for the main actions of the application.

* `exit` - exits the application.
* `toggle` - hides/shows the Windows taskbar.

The names of the keys are the same as those in Sublime Text Editor, so you may look them up at: [Sublime Text Key Bindings](https://www.sublimetext.com/docs/key_bindings.html).