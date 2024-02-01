
# Code
Consult the [main repo](https://github.com/Arman17Babaei/UEFI-System-Information-Viewer) in case this one didn't work.

## AzSakhtPkg
`AzSakhtPkg.dsc` is the main file that contains the list of all the modules that are part of the package. It also contains the build options for the package.

### MainTable
`MainTable.c` is the main file that contains the main function of the program. It is responsible for handling and forwarding the user's input.

`Pages.h` contains the definition of the static pages.

`PageState.c` contains the main code responsible for handling the user's input and displaying the pages. It formats the current page and displays it on the screen.

#### Pages
Each of the files in this folder represent a page. They may create dynamic pages if they see fit (e.g. `ACPIPage.c` creates a dynamic page for each ACPI table).

## Conf
`target.txt` contains the target IP address.