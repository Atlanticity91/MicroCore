/**
 *
 *  __  __ _             ___
 * |  \/  (_)__ _ _ ___ / __|___ _ _ ___
 * | |\/| | / _| '_/ _ \ (__/ _ \ '_/ -_)
 * |_|  |_|_\__|_| \___/\___\___/_| \___|
 *
 * MIT License
 *
 * Copyright (c) 2024- Alves Quentin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **/

#pragma once 

#include "../Log/MicroLog.h"

#define YAML_CPP_STATIC_DEFINE
#include "yaml-cpp/yaml.h"

namespace YAML {

    ////////////////////////////////////////////////////////////////////////////////////////////
    //	micro_upoint
    ////////////////////////////////////////////////////////////////////////////////////////////
    template<>
    struct convert<micro_upoint> {

        /**
         * encode static function
         * @note : Encode data for yaml writing operation.
         * @param rhs : Reference to value to encode.
         * @return : Return Yaml node.
         **/
        static Node encode( const micro_upoint& rhs ) {
            auto node = Node{ };

            node.push_back( rhs.x );
            node.push_back( rhs.y );
            node.SetStyle( EmitterStyle::Flow );

            return node;
        };

        /**
         * decode static function
         * @note : Decode data from yaml reading operation.
         * @param node : Query node to decoce.
         * @param rhs : Reference to value used to store decoded data.
         * @return : Return true when operation succeeded.
         **/
        static bool decode( const Node& node, micro_upoint& rhs ) {
            auto result = node.IsSequence( ) && node.size( ) == 2;

            if ( result ) {
                rhs.x = node[ 0 ].as<micro_upoint::value_type>( );
                rhs.y = node[ 1 ].as<micro_upoint::value_type>( );
            }

            return result;
        };

    };

    /**
     * Left hand operator
     * @note : Stream style write operator overload.
     * @param out : Current Yaml emitter intance.
     * @param value : Query value to write.
     * @return : Return current Yaml emitter instance.
     **/
    Emitter& operator<<( Emitter& out, const micro_upoint& value );

    ////////////////////////////////////////////////////////////////////////////////////////////
    //	micro_point
    ////////////////////////////////////////////////////////////////////////////////////////////
    template<>
    struct convert<micro_point> {

        /**
         * encode static function
         * @note : Encode data for yaml writing operation.
         * @param rhs : Reference to value to encode.
         * @return : Return Yaml node.
         **/
        static Node encode( const micro_point& rhs ) {
            auto node = Node{ };

            node.push_back( rhs.x );
            node.push_back( rhs.y );
            node.SetStyle( EmitterStyle::Flow );

            return node;
        };

        /**
         * decode static function
         * @note : Decode data from yaml reading operation.
         * @param node : Query node to decoce.
         * @param rhs : Reference to value used to store decoded data.
         * @return : Return true when operation succeeded.
         **/
        static bool decode( const Node& node, micro_point& rhs ) {
            auto result = node.IsSequence( ) && node.size( ) == 2;
            
            if ( result ) {
                rhs.x = node[ 0 ].as<micro_point::value_type>( );
                rhs.y = node[ 1 ].as<micro_point::value_type>( );
            }

            return result;
        };

    };

    /**
     * Left hand operator
     * @note : Stream style write operator overload.
     * @param out : Current Yaml emitter intance.
     * @param value : Query value to write.
     * @return : Return current Yaml emitter instance.
     **/
    Emitter& operator<<( Emitter& out, const micro_point& value );

    ////////////////////////////////////////////////////////////////////////////////////////////
    //	micro_vec2
    ////////////////////////////////////////////////////////////////////////////////////////////
    template<>
    struct convert<micro_vec2> {

        /**
         * encode static function
         * @note : Encode data for yaml writing operation.
         * @param rhs : Reference to value to encode.
         * @return : Return Yaml node.
         **/
        static Node encode( const micro_vec2& rhs ) {
            auto node = Node{ };

            node.push_back( rhs.x );
            node.push_back( rhs.y );
            node.SetStyle( EmitterStyle::Flow );

            return node;
        };

        /**
         * decode static function
         * @note : Decode data from yaml reading operation.
         * @param node : Query node to decoce.
         * @param rhs : Reference to value used to store decoded data.
         * @return : Return true when operation succeeded.
         **/
        static bool decode( const Node& node, micro_vec2& rhs ) {
            auto result = node.IsSequence( ) && node.size( ) == 2;

            if ( result ) {
                rhs.x = node[ 0 ].as<micro_vec2::value_type>( );
                rhs.y = node[ 1 ].as<micro_vec2::value_type>( );
            }

            return result;
        };

    };

    /**
     * Left hand operator
     * @note : Stream style write operator overload.
     * @param out : Current Yaml emitter intance.
     * @param value : Query value to write.
     * @return : Return current Yaml emitter instance.
     **/
    Emitter& operator<<( Emitter& out, const micro_vec2& value );

    ////////////////////////////////////////////////////////////////////////////////////////////
    //	micro_vec3
    ////////////////////////////////////////////////////////////////////////////////////////////
    template<>
    struct convert<micro_vec3> {

        /**
         * encode static function
         * @note : Encode data for yaml writing operation.
         * @param rhs : Reference to value to encode.
         * @return : Return Yaml node.
         **/
        static Node encode( const micro_vec3& rhs ) {
            auto node = Node{ };

            node.push_back( rhs.x );
            node.push_back( rhs.y );
            node.push_back( rhs.z );
            node.SetStyle( EmitterStyle::Flow );

            return node;
        };

        /**
         * decode static function
         * @note : Decode data from yaml reading operation.
         * @param node : Query node to decoce.
         * @param rhs : Reference to value used to store decoded data.
         * @return : Return true when operation succeeded.
         **/
        static bool decode( const Node& node, micro_vec3& rhs ) {
            auto result = node.IsSequence( ) && node.size( ) == 3;

            if ( result ) {
                rhs.x = node[ 0 ].as<micro_vec3::value_type>( );
                rhs.y = node[ 1 ].as<micro_vec3::value_type>( );
                rhs.z = node[ 2 ].as<micro_vec3::value_type>( );
            }

            return result;
        };

    };

    /**
     * Left hand operator
     * @note : Stream style write operator overload.
     * @param out : Current Yaml emitter intance.
     * @param value : Query value to write.
     * @return : Return current Yaml emitter instance.
     **/
    Emitter& operator<<( Emitter& out, const micro_vec3& value );

    ////////////////////////////////////////////////////////////////////////////////////////////
    //	micro_vec4
    ////////////////////////////////////////////////////////////////////////////////////////////
    template<>
    struct convert<micro_vec4> {

        /**
         * encode static function
         * @note : Encode data for yaml writing operation.
         * @param rhs : Reference to value to encode.
         * @return : Return Yaml node.
         **/
        static Node encode( const micro_vec4& rhs ) {
            auto node = Node{ };

            node.push_back( rhs.x );
            node.push_back( rhs.y );
            node.push_back( rhs.z );
            node.push_back( rhs.w );
            node.SetStyle( EmitterStyle::Flow );

            return node;
        };

        /**
         * decode static function
         * @note : Decode data from yaml reading operation.
         * @param node : Query node to decoce.
         * @param rhs : Reference to value used to store decoded data.
         * @return : Return true when operation succeeded.
         **/
        static bool decode( const Node& node, micro_vec4& rhs ) {
            auto result = node.IsSequence( ) && node.size( ) == 4;

            if ( result ) {
                rhs.x = node[ 0 ].as<micro_vec4::value_type>( );
                rhs.y = node[ 1 ].as<micro_vec4::value_type>( );
                rhs.z = node[ 2 ].as<micro_vec4::value_type>( );
                rhs.z = node[ 3 ].as<micro_vec4::value_type>( );
            }

            return result;
        };

    };

    /**
     * Left hand operator
     * @note : Stream style write operator overload.
     * @param out : Current Yaml emitter intance.
     * @param value : Query value to write.
     * @return : Return current Yaml emitter instance.
     **/
    Emitter& operator<<( Emitter& out, const micro_vec4& value );

};
