#ifndef ENTT_ENTITY_UTILITY_HPP
#define ENTT_ENTITY_UTILITY_HPP


#include "../config/config.h"
#include "../core/type_traits.hpp"
#include "entity.hpp"
#include <type_traits>


namespace entt {


/**
 * @brief Alias for exclusion lists.
 * @tparam Type List of types.
 */
template<typename... Type>
struct exclude_t: type_list<Type...> {};


/**
 * @brief Variable template for exclusion lists.
 * @tparam Type List of types.
 */
template<typename... Type>
inline constexpr exclude_t<Type...> exclude{};


/**
 * @brief Alias for lists of observed components.
 * @tparam Type List of types.
 */
template<typename... Type>
struct get_t: type_list<Type...>{};


/**
 * @brief Variable template for lists of observed components.
 * @tparam Type List of types.
 */
template<typename... Type>
inline constexpr get_t<Type...> get{};


/*! @brief Basic iteration policy. */
struct basic_iteration_policy {
	/**
	 * @cond TURN_OFF_DOXYGEN
	 * Internal details not to be documented.
	 */
	template<typename Entity>
	[[nodiscard]] constexpr bool operator()(const Entity) const ENTT_NOEXCEPT {
		return true;
	}
	/**
	 * Internal details not to be documented.
	 * @endcond
	 */
};


/*! @brief Tombstone aware iteration policy. */
struct skip_tombstone_policy: basic_iteration_policy {
	/**
	 * @cond TURN_OFF_DOXYGEN
	 * Internal details not to be documented.
	 */
	template<typename Entity>
	[[nodiscard]] constexpr bool operator()(const Entity entity) const ENTT_NOEXCEPT {
		return entity != tombstone;
	}
	/**
	 * Internal details not to be documented.
	 * @endcond
	 */
};


/**
 * @brief Tests whether a class represents an iteration policy.
 * @tparam Policy A possibly valid iteration policy.
 */
template<typename Policy, typename = void>
struct is_iteration_policy: std::false_type {};


/**
 * @brief Tests whether a class represents an iteration policy.
 * @tparam Policy A possibly valid iteration policy.
 */
template<typename Policy>
struct is_iteration_policy<Policy, std::enable_if_t<std::is_base_of_v<basic_iteration_policy, Policy>>>: std::true_type {};


/**
 * @brief Helper variable template.
 * @tparam Policy A possibly valid iteration policy.
 */
template<typename Policy>
inline constexpr auto is_iteration_policy_v = is_iteration_policy<Policy>::value;


}


#endif
