#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 

#define MAX_LINE 80
#define MAX_ARGS 10

int main(void) {
    char input[MAX_LINE];
    char *args[MAX_ARGS];
    char current_dir[MAX_PATH]; 
    int should_run = 1;

    while (should_run) {
        if (GetCurrentDirectory(MAX_PATH, current_dir)) {
            printf("MyWinShell [%s]> ", current_dir);
        } else {
            printf("MyWinShell> ");
        }
        fflush(stdout);
        
        if (fgets(input, MAX_LINE, stdin) == NULL) {
            break; 
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            should_run = 0;
            continue;
        }

        // Keep a backup of the original input string because strtok modifies it
        char original_input[MAX_LINE];
        strcpy(original_input, input);

        // --- PHASE 2: TOKENIZATION ---
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL; 

        if (args[0] == NULL) continue;

        // --- PHASE 2.5: HANDLE BUILT-IN COMMANDS ---
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                printf("Expected argument to \"cd\"\n");
            } else {
                if (!SetCurrentDirectory(args[1])) {
                    printf("Directory not found: %s\n", args[1]);
                }
            }
            continue; 
        }

        if (strcmp(args[0], "about") == 0) {
            printf("\n==================================================\n");
            printf(" Welcome to MyWinShell v1.0\n");
            printf(" Developer: Durwankur Dange\n");
            printf(" Language:  C (Win32 API Kernel Integration)\n");
            printf(" Status:    Fully Operational\n");
            printf("==================================================\n\n");
            continue; 
        }

        // --- PERMANENT FIX: INTERCEPT CMD INTERNAL COMMANDS ---
        char execution_command[MAX_LINE + 20] = ""; 
        
        if (strcmp(args[0], "dir") == 0 || strcmp(args[0], "mkdir") == 0 || 
            strcmp(args[0], "rmdir") == 0 || strcmp(args[0], "echo") == 0 || 
            strcmp(args[0], "cls") == 0) 
        {
            // Automatically prepend 'cmd.exe /c ' to the original user input
            strcpy(execution_command, "cmd.exe /c ");
            strcat(execution_command, original_input);
        } else {
            // For external applications (notepad, calc, ping), use input as-is
            strcpy(execution_command, original_input);
        }

        // --- PHASE 3: WINDOWS PROCESS EXECUTION ---
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        // Pass our newly formatted execution_command to CreateProcess
        if (!CreateProcess(NULL, execution_command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            printf("Command '%s' not recognized.\n", args[0]);
        } else {
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    }
    return 0;
}
