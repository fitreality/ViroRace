@echo Set objShell = CreateObject("Shell.Application") > sudo.tmp.vbs
@echo dim fso: set fso = CreateObject("Scripting.FileSystemObject") >> sudo.tmp.vbs
@echo CurrentDirectory = fso.GetAbsolutePathName(".") >> sudo.tmp.vbs
@echo args = Right("%*", (Len("%*") - Len("%1"))) >> sudo.tmp.vbs
@echo objShell.ShellExecute "%1", args, CurrentDirectory, "runas" >> sudo.tmp.vbs
@cscript sudo.tmp.vbs