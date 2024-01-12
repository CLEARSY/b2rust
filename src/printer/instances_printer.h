#ifndef INSTANCES_PRINTER_H
#define INSTANCES_PRINTER_H

#include <ostream>
#include <unordered_map>
#include <string>
#include <vector>

#include "../parser/miscellaneous.h"

/*!
 * \brief The InstancesPrinter class allows to print the instances of a b2rust module
 */
class InstancesPrinter {
public:
    /*!
     * \brief The name of the file containing in which the instances container will
     * be generated
     */
    static const std::string INSTANCES_FILENAME;
    /*!
     * \brief An accessor on the generated module name
     * \return the name of the generated module
     */
    static const std::string getModuleName();
    /*!
     * \brief Provides the name of the getter on the struct containing the instances of the given type
     * \param type
     * The type of the instances
     * \return the name of the getter on the struct containing the instances of the given type
     */
    static std::string getContainerGetterName(std::string type);
    /*!
     * \brief Provides the getter name for a given instance
     * \param instance
     * The instance
     * \return the getter name for a given instance
     */
    static std::string getGetterName(std::string instance);
    /*!
     * \brief Provides the name of a getter of the instances of a type
     * \param type
     * The type
     * \return the name of a getter of the instances of a type
     */
    static std::string getInstancesGetterName(std::string type);
    /*!
     * \brief Provides the constructor name for a given type
     * \param type
     * The type
     * \return the constructor name for a given type
     */
    static std::string getConstructorName(std::string type);
    /*!
     * \brief Add a module to the instances to print
     * \param context
     * The context of the module containing all the usefull informations
     * to print
     */
    void addModule(Context& context);
    /*!
     * \brief Create a file containing the instances module. The path of the generated
     * file will be the one given to the contructor
     * \param directory
     * The directory in which to write the file
     */
    void print(std::string directory);

private:
    /*!
     * \brief A map of shape Machine Type -> instances of the machine
     */
    std::unordered_map<std::string, std::vector<std::string>> m_type_to_instances;
    /*!
     * \brief A map of shape Machine Type -> rust container struct
     */
    std::unordered_map<std::string, std::string> m_type_to_struct;
    /*!
     * \brief A constant to indent the code
     */
    const std::string m_indent = "    ";
    /*!
     * \brief A separator for the comment
     */
    const std::string m_separator = std::string(120, '=') + "\n";
    /*!
     * \brief Add the instances module to an ostream
     * \param stream
     * The stream on which to add the instances module
     */
    void print(std::ostream& stream);
    /*!
     * \brief Print m_separator between comment on a given stream
     * \param stream
     * The stream
     */
    void printSeparationInComment(std::ostream& stream);
    /*!
     * \brief Print a comment on a stream prefixed and suffixed by a separator
     * \param stream
     * The stream
     * \param comment
     * The comment
     */
    void printCommentHeader(std::ostream& stream, std::string comment);
    /*!
     * \brief Print all the needed uses on the given stream
     * \param stream
     * The stream
     */
    void printUses(std::ostream& stream);
    /*!
     * \brief Print all the needed structs on the given stream
     * \param stream
     * The stream
     */
    void printStructs(std::ostream& stream);
    /*!
     * \brief Print the constructor of a type on a given stream
     * \param stream
     * The stream
     * \param type
     * The type
     */
    void printConstructor(std::ostream& stream, std::string type);
    /*!
     * \brief Print the getters of a type on a given stream
     * \param stream
     * The stream
     * \param type
     * The type
     */
    void printGetters(std::ostream& stream, std::string type);
    /*!
     * \brief Print the static getters which allow to access to the instances of a machine
     * on a given stream
     * \param stream
     * The stream
     */
    void printStaticGetters(std::ostream& stream);
    /*!
     * \brief Print the constructors used to instanciate a machine container on a given stream
     * \param stream
     * The stream
     */
    void printInstancesConstructor(std::ostream& stream);
    /*!
     * \brief Print the getters of an instances container on a given stream
     * \param stream
     * The stream
     */
    void printInstancesGetter(std::ostream& stream);

};

#endif // INSTANCES_PRINTER_H
