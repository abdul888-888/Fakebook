#include <iostream>
#include <limits>
#include <string>
#include "Facebook.h"
using namespace std;

void displayMenu() {
    cout << "\n=== Facebook Menu ===\n";
    cout << "1. Sign Up\n";
    cout << "2. Login\n";
    cout << "3. Logout\n";
    cout << "4. Show My Profile\n";
    cout << "5. View Another User's Profile\n";
    cout << "6. Create Post\n";
    cout << "7. Show My Posts\n";
    cout << "8. View Friend's Posts\n";
    cout << "9. News Feed\n";
    cout << "10. Edit Post\n";
    cout << "11. Delete Post\n";
    cout << "12. Send Friend Request\n";
    cout << "13. Show Friend Requests\n";
    cout << "14. Accept Friend Request\n";
    cout << "15. Reject Friend Request\n";
    cout << "16. Show My Friends\n";
    cout << "17. Remove Friend\n";
    cout << "18. Like Post\n";
    cout << "19. Unlike Post\n";
    cout << "20. Comment on Post\n";
    cout << "21. Delete Comment\n";
    cout << "22. Search Users by ID\n";
    cout << "23. Search Users by Name\n";
    cout << "24. Search Users by Email\n";
    cout << "25. Mutual Friends\n";
    cout << "26. Friend Suggestions\n";
    cout << "27. Save Data\n";
    cout << "28. Exit\n";
    cout << "Choose an option: ";
}

int readInt(const string& prompt, int minValue = numeric_limits<int>::min(),
    int maxValue = numeric_limits<int>::max()) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a valid number";
        if (minValue != numeric_limits<int>::min() || maxValue != numeric_limits<int>::max()) {
            cout << " between " << minValue << " and " << maxValue;
        }
        cout << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readLine(const string& prompt, bool allowEmpty = false) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (allowEmpty || !value.empty()) return value;
        cout << "This field cannot be empty.\n";
    }
}

int main() {
    Facebook facebook;
    bool running = true;

    cout << "Welcome to Facebook Console App!\n";

    while (running) {
        displayMenu();
        int choice = readInt("", 1, 28);

        switch (choice) {
        case 1: {
            int id = readInt("Enter User ID: ", 1);
            string name = readLine("Enter Name: ");
            string email = readLine("Enter Email: ");
            string password = readLine("Enter Password: ");
            string gender = readLine("Enter Gender (Male/Female/Other): ");
            int age = readInt("Enter Age: ", 13, 120);
            int privacy = readInt("Public Profile? (1 for Yes, 0 for No): ", 0, 1);
            facebook.signUp(id, name, email, password, gender, age, privacy == 1);
            break;
        }

        case 2: {
            int loginChoice = readInt("Login by: 1. Email 2. User ID: ", 1, 2);
            string password;
            if (loginChoice == 1) {
                string email = readLine("Enter Email: ");
                password = readLine("Enter Password: ");
                facebook.login(email, password);
            }
            else {
                int id = readInt("Enter User ID: ", 1);
                password = readLine("Enter Password: ");
                facebook.login(id, password);
            }
            break;
        }

        case 3:
            facebook.logout();
            break;

        case 4:
            facebook.showMyProfile();
            break;

        case 5: {
            int userID = readInt("Enter User ID to view: ", 1);
            facebook.viewUserProfile(userID);
            break;
        }

        case 6: {
            string content = readLine("Enter post content: ");
            facebook.createPost(content);
            break;
        }

        case 7:
            facebook.showMyPosts();
            break;

        case 8: {
            int userID = readInt("Enter Friend's User ID: ", 1);
            facebook.showPostsForUser(userID);
            break;
        }

        case 9:
            facebook.showNewsFeed();
            break;

        case 10: {
            int postID = readInt("Enter your Post ID to edit: ", 1);
            string content = readLine("Enter new post content: ");
            facebook.editPost(postID, content);
            break;
        }

        case 11: {
            int postID = readInt("Enter your Post ID to delete: ", 1);
            facebook.deletePost(postID);
            break;
        }

        case 12: {
            int friendID = readInt("Enter Friend's User ID: ", 1);
            facebook.sendFriendRequest(friendID);
            break;
        }

        case 13:
            facebook.showFriendRequests();
            break;

        case 14: {
            int fromUserID = readInt("Enter User ID to accept: ", 1);
            facebook.acceptFriendRequest(fromUserID);
            break;
        }

        case 15: {
            int fromUserID = readInt("Enter User ID to reject: ", 1);
            facebook.rejectFriendRequest(fromUserID);
            break;
        }

        case 16:
            facebook.showMyFriends();
            break;

        case 17: {
            int friendID = readInt("Enter Friend's User ID to remove: ", 1);
            facebook.removeFriend(friendID);
            break;
        }

        case 18: {
            int userID = readInt("Enter User ID whose post to like: ", 1);
            int postID = readInt("Enter Post ID to like: ", 1);
            facebook.likePost(userID, postID);
            break;
        }

        case 19: {
            int userID = readInt("Enter User ID whose post to unlike: ", 1);
            int postID = readInt("Enter Post ID to unlike: ", 1);
            facebook.unlikePost(userID, postID);
            break;
        }

        case 20: {
            int userID = readInt("Enter User ID whose post to comment on: ", 1);
            int postID = readInt("Enter Post ID to comment on: ", 1);
            string comment = readLine("Enter your comment: ");
            facebook.commentOnPost(userID, postID, comment);
            break;
        }

        case 21: {
            int ownerID = readInt("Enter post owner's User ID: ", 1);
            int postID = readInt("Enter Post ID: ", 1);
            int commentID = readInt("Enter Comment ID to delete: ", 1);
            facebook.deleteComment(ownerID, postID, commentID);
            break;
        }

        case 22: {
            int id = readInt("Enter User ID to search: ", 1);
            facebook.searchByID(id);
            break;
        }

        case 23: {
            string name = readLine("Enter name or part of name: ");
            facebook.searchByName(name);
            break;
        }

        case 24: {
            string email = readLine("Enter Email to search: ");
            facebook.searchByEmail(email);
            break;
        }

        case 25: {
            int id = readInt("Enter User ID to compare with: ", 1);
            facebook.showMutualFriends(id);
            break;
        }

        case 26:
            facebook.showFriendSuggestions();
            break;

        case 27:
            facebook.saveData();
            cout << "Data saved successfully.\n";
            break;

        case 28:
            facebook.saveData();
            cout << "Thank you for using Facebook Console App!\n";
            running = false;
            break;
        }
    }

    return 0;
}
