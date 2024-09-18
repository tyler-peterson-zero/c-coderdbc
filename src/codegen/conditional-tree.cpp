#include "conditional-tree.h"
#include "helpers/formatter.h"

ConditionalTree::ConditionalTree()
{
}

// this method performs printing tree-viewed frames collection
// to proper source code
std::string ConditionalTree::WriteCode(const ConditionalTree_t* tree, std::string& outstr, uint8_t intend)
{
  if (tree != nullptr)
  {
    std::string temp;
    bool misra_close = false;
    if (tree->Type == ConditionalType::Cond)
    {
      temp = StrPrint("if (%s)",tree->ConditionExpresion.c_str());
      PrintCode(temp, intend);
      temp = StrPrint("{");
      PrintCode(temp, intend);

      WriteCode(tree->High, outstr, intend + 2);

      if (tree->Low != nullptr)
      {
        if (tree->Low->Type == ConditionalType::Express)
        {
          temp = StrPrint("}");
          PrintCode(temp, intend);
          temp = StrPrint("else if (%s)", tree->Low->ConditionExpresion.c_str());
          PrintCode(temp, intend);
          temp = StrPrint("{");
          PrintCode(temp, intend);
          misra_close = true;
        }
        else
        {
          temp =StrPrint("}"); 
          PrintCode(temp, intend);
          temp =StrPrint("else");
          PrintCode(temp, intend);
          temp =StrPrint("{"); 
          PrintCode(temp, intend);
          
        }

        WriteCode(tree->Low, outstr, intend + 2);
      }
      else 
      {
        if(misra_close==true)
        {
          temp =StrPrint("}"); 
          PrintCode(temp, intend);
          temp =StrPrint("else");
          PrintCode(temp, intend);
          temp =StrPrint("{"); 
          PrintCode(temp, intend);
          temp =StrPrint("  //MISRA-C");
          PrintCode(temp, intend);
          temp =StrPrint("}"); 
          PrintCode(temp, intend);
          misra_close=false;
        }
        else
        {
          temp =StrPrint("}"); 
          PrintCode(temp, intend);
        }
      }

      if (tree->Low != nullptr)
      {
        if(misra_close==true)
        {
          temp =StrPrint("}"); 
          PrintCode(temp, intend);
          temp =StrPrint("else");
          PrintCode(temp, intend);
          temp =StrPrint("{"); 
          PrintCode(temp, intend);
          temp =StrPrint("  //MISRA-C");
          PrintCode(temp, intend);
          temp =StrPrint("}"); 
          PrintCode(temp, intend);
          misra_close=false;
        }
        else
        {
          temp =StrPrint("}"); 
          PrintCode(temp, intend);
        }
      }
    }
    else
    {
      temp = StrPrint("%s", tree->UtilCodeBody.c_str());
      PrintCode(temp, intend);
    }
  }

  return codestr;
}

void ConditionalTree::PrintCode(std::string& str, uint8_t indent)
{
  while (indent--)
  {
    codestr += " ";
  }

  codestr += str;
  codestr += "\n";
}


void ConditionalTree::DeleteTree(ConditionalTree_t* tree)
{
  if (tree != nullptr)
  {
    if (tree->Low != nullptr)
    {
      DeleteTree(tree->Low);
    }

    if (tree->High != nullptr)
    {
      DeleteTree(tree->High);
    }

    delete tree;
  }
}
