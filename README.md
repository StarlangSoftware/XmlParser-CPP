For Developers
============
You can also see [C](https://github.com/starlangsoftware/XmlParser-C), [Java](https://github.com/starlangsoftware/XmlParser), or [Js](https://github.com/starlangsoftware/XmlParser-Js) repository.

## Requirements

* [C++ Compiler](#cpp)
* [Git](#git)


### CPP
To check if you have compatible C++ Compiler installed,
* Open CLion IDE 
* Preferences >Build,Execution,Deployment > Toolchain  

### Git

Install the [latest version of Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

## Download Code

In order to work on code, create a fork from GitHub page. 
Use Git for cloning the code to your local or below line for Ubuntu:

	git clone <your-fork-git-link>

A directory called Util-CPP will be created. Or you can use below link for exploring the code:

	git clone https://github.com/starlangsoftware/XmlParser-CPP.git

## Open project with CLion IDE

To import projects from Git with version control:

* Open CLion IDE , select Get From Version Control.

* In the Import window, click URL tab and paste github URL.

* Click open as Project.

Result: The imported project is listed in the Project Explorer view and files are loaded.


## Compile

**From IDE**

After being done with the downloading and opening project, select **Build Project** option from **Build** menu.

Detailed Description
============

In order to load an xml document, we use the constructor

    XmlDocument doc = XmlDocument(fileName);
    
and parse with the parse method

    doc.parse();
    
Root node of the document can be obtained via the getFirstChild method:

    rootNode = doc.getFirstChild();
  
For example, to iterate over the first level tags in the xml file one can use

    XmlElement* rootNode = doc.getFirstChild();
    XmlElement* childNode = rootNode->getFirstChild();
    while (childNode != nullptr){
      ...
      childNode = childNode->getNextSibling();
    }

Tag name can be obtained via getName, pcData via getPcData methods.
