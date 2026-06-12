// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_LINE 80 // The maximum length of a command

// int main(void) {
//     char input[MAX_LINE];
//     int should_run = 1;

//     while (should_run) {
//         printf("DurwankurShell> ");
//         fflush(stdout);
        
//         // Read input from user
//         if (fgets(input, MAX_LINE, stdin) == NULL) {
//             break; 
//         }

//         // Remove the newline character at the end of input
//         input[strcspn(input, "\n")] = '\0';

//         // Built-in command to exit
//         if (strcmp(input, "exit") == 0) {
//             should_run = 0;
//             continue;
//         }

//         printf("You typed: %s\n", input);
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_LINE 80
// #define MAX_ARGS 10 // Maximum number of arguments a command can have

// int main(void) {
//     char input[MAX_LINE];
//     char *args[MAX_ARGS]; // Array of string pointers to hold our arguments
//     int should_run = 1;

//     while (should_run) {
//         printf("MyShell> ");
//         fflush(stdout);
        
//         if (fgets(input, MAX_LINE, stdin) == NULL) {
//             break; 
//         }

//         input[strcspn(input, "\n")] = '\0';

//         if (strcmp(input, "exit") == 0) {
//             should_run = 0;
//             continue;
//         }

//         // --- PHASE 2: TOKENIZATION START ---
//         int i = 0;
        
//         // Get the first token (the actual command, e.g., "ls")
//         args[i] = strtok(input, " ");

//         // Loop to get the rest of the tokens (the arguments, e.g., "-l", "-a")
//         while (args[i] != NULL && i < MAX_ARGS - 1) {
//             i++;
//             args[i] = strtok(NULL, " "); // Pass NULL to keep chopping the same string
//         }
        
//         args[i] = NULL; // Explicitly set the last element to NULL for execvp
//         // --- PHASE 2: TOKENIZATION END ---


//         // Let's print out what we captured to verify it works!
//         if (args[0] != NULL) {
//             printf("Command to execute: %s\n", args[0]);
//             for(int j = 1; args[j] != NULL; j++) {
//                 printf("Argument %d: %s\n", j, args[j]);
//             }
//         }
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>    // Added for fork() and execvp()
// #include <sys/types.h> // Added for pid_t
// #include <sys/wait.h>  // Added for wait()

// #define MAX_LINE 80
// #define MAX_ARGS 10

// int main(void) {
//     char input[MAX_LINE];
//     char *args[MAX_ARGS];
//     int should_run = 1;

//     while (should_run) {
//         printf("MyShell> ");
//         fflush(stdout);
        
//         if (fgets(input, MAX_LINE, stdin) == NULL) {
//             break; 
//         }

//         input[strcspn(input, "\n")] = '\0';

//         if (strcmp(input, "exit") == 0) {
//             should_run = 0;
//             continue;
//         }

//         // --- PHASE 2: TOKENIZATION ---
//         int i = 0;
//         args[i] = strtok(input, " ");
//         while (args[i] != NULL && i < MAX_ARGS - 1) {
//             i++;
//             args[i] = strtok(NULL, " ");
//         }
//         args[i] = NULL; 

//         // --- PHASE 3: OS SYSTEM CALLS START ---
//         if (args[0] != NULL) {
//             pid_t pid = fork(); // 1. Clone the current shell process

//             if (pid < 0) {
//                 // Fork failed (very rare, usually out of system memory)
//                 perror("Fork Failed");
//             } 
//             else if (pid == 0) {
//                 // 2. CHILD PROCESS: Replace child's memory with the command
//                 if (execvp(args[0], args) < 0) {
//                     perror("Command not found"); // Error if command doesn't exist
//                     exit(1); 
//                 }
//             } 
//             else {
//                 // 3. PARENT PROCESS (Your Shell): Pause until child finishes
//                 wait(NULL); 
//             }
//         }
//         // --- PHASE 3: OS SYSTEM CALLS END ---
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <windows.h> // Replace unistd.h and sys/wait.h with this

// #define MAX_LINE 80
// #define MAX_ARGS 10

// int main(void) {
//     char input[MAX_LINE];
//     char *args[MAX_ARGS];
//     int should_run = 1;

//     while (should_run) {
//         printf("MyWinShell> ");
//         fflush(stdout);
        
//         if (fgets(input, MAX_LINE, stdin) == NULL) {
//             break; 
//         }

//         input[strcspn(input, "\n")] = '\0';

//         if (strcmp(input, "exit") == 0) {
//             should_run = 0;
//             continue;
//         }

//         // --- PHASE 2: TOKENIZATION ---
//         int i = 0;
//         args[i] = strtok(input, " ");
//         while (args[i] != NULL && i < MAX_ARGS - 1) {
//             i++;
//             args[i] = strtok(NULL, " ");
//         }
//         args[i] = NULL; 

//         // --- PHASE 3: WINDOWS PROCESS EXECUTION ---
//         if (args[0] != NULL) {
//             // Windows needs structures to manage the state of the new process
//             STARTUPINFO si;
//             PROCESS_INFORMATION pi;

//             // Initialize the memory memory spaces to zero
//             ZeroMemory(&si, sizeof(si));
//             si.cb = sizeof(si);
//             ZeroMemory(&pi, sizeof(pi));

//             // Windows CreateProcess requires the full command line input string back
//             // To make it simple, we can re-pass the original unmodified input
//             if (!CreateProcess(
//                     NULL,           // Application name (NULL means use command line string)
//                     input,          // Command line arguments
//                     NULL,           // Process handle not inheritable
//                     NULL,           // Thread handle not inheritable
//                     FALSE,          // Set handle inheritance to FALSE
//                     0,              // No creation flags
//                     NULL,           // Use parent's environment block
//                     NULL,           // Use parent's starting directory 
//                     &si,            // Pointer to STARTUPINFO structure
//                     &pi             // Pointer to PROCESS_INFORMATION structure
//                 )) 
//             {
//                 printf("Command execution failed. Error Code: %lu\n", GetLastError());
//             } else {
//                 // Parent explicitly waits until the child process exits
//                 WaitForSingleObject(pi.hProcess, INFINITE);

//                 // Close process and thread handles
//                 CloseHandle(pi.hProcess);
//                 CloseHandle(pi.hThread);
//             }
//         }
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <windows.h> 

// #define MAX_LINE 80
// #define MAX_ARGS 10

// int main(void) {
//     char input[MAX_LINE];
//     char *args[MAX_ARGS];
//     char current_dir[MAX_PATH]; // Buffer to store the current path
//     int should_run = 1;

//     while (should_run) {
//         // Get and display the actual current working directory
//         if (GetCurrentDirectory(MAX_PATH, current_dir)) {
//             printf("MyWinShell [%s]> ", current_dir);
//         } else {
//             printf("MyWinShell> ");
//         }
//         fflush(stdout);
        
//         if (fgets(input, MAX_LINE, stdin) == NULL) {
//             break; 
//         }

//         input[strcspn(input, "\n")] = '\0';

//         if (strcmp(input, "exit") == 0) {
//             should_run = 0;
//             continue;
//         }

//         // --- PHASE 2: TOKENIZATION ---
//         int i = 0;
// args[i] = strtok(input, " ");
// while (args[i] != NULL && i < MAX_ARGS - 1) {
//     i++;
//     args[i] = strtok(NULL, " ");
// }
// args[i] = NULL; 

// if (args[0] == NULL) continue;

// // --- PHASE 2.5: HANDLE BUILT-IN COMMANDS ---

// // 1. Existing 'cd' command handler
// if (strcmp(args[0], "cd") == 0) {
//     if (args[1] == NULL) {
//         printf("Expected argument to \"cd\"\n");
//     } else {
//         if (!SetCurrentDirectory(args[1])) {
//             printf("Directory not found: %s\n", args[1]);
//         }
//     }
//     continue; // Skip CreateProcess
// }

// // 2. NEW 'about' command handler (ADD THIS HERE)
// if (strcmp(args[0], "about") == 0) {
//     // printf("\n==================================================\n");
//     // printf("  __  __eV_   _  _  _ _  ____  _          _ _ \n");
//     // printf(" |  \\/  \\ \\ / / | || | |/ ___|| |    ___ | | |\n");
//     // printf(" | |\\/| |\\ V /  | || |_| \\___ \\| |   / _ \\| | |\n");
//     // printf(" | |  | | | |   |__   _| |___) | |__|  __/|_|_|\n");
//     // printf(" |_|  |_| |_|      |_|  |____/|_____\\___|(_|_)\n");
//     printf("==================================================\n");
//     printf(" Developer: Durwankur Dange\n");
//     printf(" Language:  C (Win32 API Kernel Integration)\n");
//     printf(" Status:    Fully Operational\n");
//     printf("==================================================\n\n");
//     continue; // Skip CreateProcess so it doesn't look for an external "about.exe"
// }

//         // --- PHASE 3: WINDOWS PROCESS EXECUTION ---
//         STARTUPINFO si;
//         PROCESS_INFORMATION pi;

//         ZeroMemory(&si, sizeof(si));
//         si.cb = sizeof(si);
//         ZeroMemory(&pi, sizeof(pi));

//         // Reconstruct a simple execution string from input for CreateProcess
//         if (!CreateProcess(NULL, input, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
//             printf("Command '%s' not recognized.\n", args[0]);
//         } else {
//             WaitForSingleObject(pi.hProcess, INFINITE);
//             CloseHandle(pi.hProcess);
//             CloseHandle(pi.hThread);
//         }
//     }
//     return 0;
// }


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