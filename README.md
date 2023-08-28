## Logic of Programming - Contact Manager README

This C program implements a contact manager with dynamic memory allocation and file handling capabilities. The program provides a menu with options to insert, search, and delete contacts. Contacts are stored in a dynamically allocated array and can be saved and loaded from both text and binary files.

### List L11 (Structures and Dynamic Allocation)

1. **Contact Structures**: The implementation involves creating a `contact` structure that stores the name, phone number, and date of birth.

2. **Option Menu**: The program offers an interactive menu with options to perform actions such as inserting, searching, and deleting contacts.

3. **Insert Contact**: Users can add new contacts to the manager by filling in the fields for name, phone number, and date of birth.

4. **Search Contact**: The search functionality allows users to find contacts by searching for specific substrings in their names.

5. **Delete Contact**: Users can remove contacts from the manager. Deletion requires searching for the contact first, similar to the search functionality.

6. **Dynamic Memory Allocation**: The contact data is stored in a dynamically allocated array, ensuring efficient memory usage and flexibility in managing contacts.

### List L12 (File Handling)

1. **Load Contacts from File**: At program startup, all contacts are loaded from a file into the contact manager.

2. **Save Contacts to File**: When the program is closed, contacts are saved to a file, allowing persistent storage.

3. **Text and Binary Files**: The program supports saving contacts in both text and binary file formats. Users can choose to load from and save to either format.

4. **User Choice**: Users are prompted to choose whether to load contacts from a text or binary file when the program starts.

### Instructions

1. Compile and run the program.
2. Use the menu options to manage contacts: insert, search, and delete.
3. Contacts are stored dynamically and can be saved to text and binary files.
4. Follow the on-screen instructions to interact with the program.

Please note that this version of the program focuses on List L11 requirements. Feel free to implement List L12 features to enhance the functionality.

This program is provided as part of a practical assignment. Please ensure to understand and customize it as needed for your learning purposes.
