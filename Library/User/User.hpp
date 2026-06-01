#pragma once
#include <string>

/// \class User
/// \brief An abstract base class representing a user in the library system.
///
/// This class holds common data for all users, such as username, password, 
/// and privilege level (admin status). It provides interfaces for serialization 
/// and deserialization.
class User {
protected:
    /// \brief The user's account name.
    std::string m_username;
    
    /// \brief The user's password in plain text.
    std::string m_password;
    
    /// \brief Flag indicating whether the user has administrator privileges.
    bool m_admin;

    /// \brief Protected constructor to initialize base user properties.
    /// \param username The account username.
    /// \param password The account password.
    /// \param admin True if the user is an administrator, false otherwise.
    User(std::string username, std::string password, bool admin);

public:
    /// \brief The character used to separate fields when saving to a file.
    static constexpr char m_DELIMITER{ '$' };

    /// \brief Serializes the user's data to a file.
    /// \param filename The path to the file where the user data should be appended.
    ///
    /// This is a pure virtual function that must be implemented by derived classes.
    virtual void serialize(const std::string& filename) const = 0;

    /// \brief Deserializes a user from a specific line in a data file.
    /// \param filename The path to the file to read from.
    /// \param line The line number (1-indexed) to parse.
    /// \return A dynamically allocated pointer to a derived User object (e.g., Client or Admin).
    /// \note The caller is responsible for managing the memory of the returned object.
    static User* deserialize(const std::string& filename, unsigned line);

    /// \brief Retrieves the username.
    /// \return A constant reference to the user's username.
    const std::string& getUsername() const;

    /// \brief Retrieves the password.
    /// \return A constant reference to the user's password.
    const std::string& getPassword() const;

    /// \brief Checks if the user is an administrator.
    /// \return True if the user is an admin, false otherwise.
    bool isAdmin() const;

    /// \brief Virtual destructor for proper polymorphic cleanup.
    virtual ~User() = default;
};