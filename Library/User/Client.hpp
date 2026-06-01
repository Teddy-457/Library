#pragma once
#include <string>
#include "User.hpp"

/// \class Client
/// \brief Represents a standard library user with regular privileges.
///
/// The Client class inherits from User and implements serialization
/// which the Admin class also inherits. Standard clients cannot add or remove users or books.
class Client : public User {
protected:
    /// \brief Protected constructor for derived classes (like Admin) to set the admin flag.
    /// \param username The account username.
    /// \param password The account password.
    /// \param is_admin Boolean indicating if the user is an admin.
    Client(std::string username, std::string password, bool is_admin);

public:
    // Deleted default constructor and copying/moving semantics
    Client() = delete;
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client(Client&&) noexcept = delete;
    Client& operator=(Client&&) noexcept = delete;

    /// \brief Default virtual destructor.
    ~Client() override = default;

    /// \brief Constructs a new Client user.
    /// \param username The account username.
    /// \param password The account password.
    ///
    /// Initializes the base User with the provided credentials and sets the admin flag to false.
    Client(std::string username, std::string password);

    /// \brief Serializes the Client's data to a file.
    /// \param filename The path to the file where the user data should be appended.
    ///
    /// Writes the Client's specific type identifier and properties to the file 
    /// using the standard delimiter format.
    void serialize(const std::string& filename) const final;

    /// \brief Deserializes a Client from an open file stream.
    /// \param file A reference to an open input file stream positioned at the user's data.
    /// \return A dynamically allocated pointer to the newly created Client.
    ///
    /// \note The caller is responsible for deleting the returned Client object.
    static Client* deserialize(std::ifstream& file);
};
