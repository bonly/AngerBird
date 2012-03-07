for %%c in (*.mak) do nmake -f %%c %1

del test.bin

rename *.mod test.bin
