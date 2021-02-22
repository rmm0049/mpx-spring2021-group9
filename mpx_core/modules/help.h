/**
  @file help.h
*/

#ifndef _HELP_H
#define _HELP_H


/*
  Procedure..: help_version
  Description..:processes the help command and displays help page for version
  Params..:char *msg
*/

void help(char *msg);

/**
  used in help() to print help page to terminal
  @param int count, char *name, char *usage, char *descript,
*/

void display_help(int count, char *name, char *usage, char *descript);

#endif
